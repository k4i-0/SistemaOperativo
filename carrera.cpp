#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>

std::mutex mtx;  // Mutex para manejar la salida a la terminal de manera segura

// Colores para diferenciar los autos
const std::string RESET = "\033[0m";
const std::string ROJO = "\033[31m";
const std::string VERDE = "\033[32m";
const std::string AMARILLO = "\033[33m";
const std::string AZUL = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";

// Progreso visual
void mostrarProgreso(int autoID, int progreso, int distanciaTotal, std::string color) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << color << "Auto" << autoID << ": [";
    
    int porcentaje = (progreso * 20) / distanciaTotal;  // Progreso visual sobre 20 caracteres
    for (int i = 0; i < 20; ++i) {
        if (i < porcentaje)
            std::cout << "=";
        else
            std::cout << " ";
    }
    
    std::cout << "] " << progreso << " metros" << RESET << std::endl;
}

// Función para simular la carrera de un auto
void carreraAuto(int autoID, int distanciaTotal, std::vector<int>& posiciones, int& lugar) {
    int progreso = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> avanceDist(1, 10); // El auto avanza entre 1 y 10 metros
    std::uniform_int_distribution<> velocidad(100, 500); // El auto cambia su velocidad entre 100 y 500 ms

    std::string color;
    switch (autoID % 6) {
        case 0: color = ROJO; break;
        case 1: color = VERDE; break;
        case 2: color = AMARILLO; break;
        case 3: color = AZUL; break;
        case 4: color = MAGENTA; break;
        case 5: color = CYAN; break;
    }

    while (progreso < distanciaTotal) {
        int distancia = avanceDist(gen);
        progreso += distancia;
        if (progreso > distanciaTotal) progreso = distanciaTotal;

        // Mostrar el progreso del auto
        mostrarProgreso(autoID, progreso, distanciaTotal, color);

        // Esperar un tiempo aleatorio antes de avanzar nuevamente
        std::this_thread::sleep_for(std::chrono::milliseconds(velocidad(gen)));
    }

    // Cuando el auto termina la carrera, indicar su lugar
    {
        std::lock_guard<std::mutex> lock(mtx);
        lugar++;
        std::cout << color << "Auto" << autoID << " termina la carrera en el lugar " << lugar << "!" << RESET << std::endl;
        posiciones[autoID] = lugar;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <distanciaTotal> <numAutos>" << std::endl;
        return 1;
    }

    int distanciaTotal, numAutos;
    try {
        distanciaTotal = std::stoi(argv[1]);
        numAutos = std::stoi(argv[2]);
    } catch (std::exception& e) {
        std::cerr << "Error: Los parámetros deben ser números enteros válidos." << std::endl;
        return 1;
    }

    std::cout << "Distancia total carrera: " << distanciaTotal << " metros" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::vector<std::thread> autos;
    std::vector<int> posiciones(numAutos, 0); // Para almacenar el lugar final de cada auto
    int lugar = 0;

    // Crear una hebra para cada auto
    for (int i = 0; i < numAutos; ++i) {
        autos.push_back(std::thread(carreraAuto, i, distanciaTotal, std::ref(posiciones), std::ref(lugar)));
    }

    // Esperar a que todos los autos terminen la carrera
    for (auto& t : autos) {
        t.join();
    }

    // Mostrar los resultados finales
    std::cout << "Lugar   Auto" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (int i = 1; i <= numAutos; ++i) {
        for (int j = 0; j < numAutos; ++j) {
            if (posiciones[j] == i) {
                std::cout << "  " << i << "      Auto" << j << std::endl;
            }
        }
    }

    return 0;
}
