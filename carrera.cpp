#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>  // Para srand y rand
#include <ctime>    // Para time
#include <chrono>   // Para sleep_for
#include <mutex>    // Para manejar la sincronización de las salidas a consola

std::mutex mtx;  // Mutex para asegurar que las impresiones en consola no se mezclen

// Función que simula la carrera de un auto
void correrAuto(int id, int distanciaTotal, int& lugarLlegada, std::vector<int>& posiciones) {
    int distanciaRecorrida = 0;

    while (distanciaRecorrida < distanciaTotal) {
        // Avanza una distancia aleatoria (entre 1 y 10 metros)
        int avance = rand() % 10 + 1;
        distanciaRecorrida += avance;

        // Asegura que no se pase de la distancia total
        if (distanciaRecorrida > distanciaTotal) {
            distanciaRecorrida = distanciaTotal;
        }

        // Detiene el auto por un tiempo aleatorio (entre 100 y 500 milisegundos)
        int velocidad = rand() % 401 + 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(velocidad));

        // Bloquea el mutex para imprimir el progreso del auto
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "\033[1;3" << id+1 << "m"  // Asignación de color
                      << "Auto" << id << " avanza " << avance << " metros (total: " 
                      << distanciaRecorrida << " metros)\033[0m" << std::endl;
        }
    }

    // Una vez terminado, asigna su lugar de llegada
    {
        std::lock_guard<std::mutex> lock(mtx);
        lugarLlegada++;
        posiciones[id] = lugarLlegada;
        std::cout << "\033[1;3" << id+1 << "m"  // Asignación de color
                  << "Auto" << id << " termina la carrera en el lugar " << lugarLlegada 
                  << "!\033[0m" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Verifica que se proporcionen los argumentos correctos
    if (argc != 3) {
        std::cerr << "Uso: ./carrera <distancia_total> <numero_autos>" << std::endl;
        return 1;
    }

    // Inicializa las variables de distancia y número de autos
    int distanciaTotal, numAutos;
    try {
        distanciaTotal = std::stoi(argv[1]);
        numAutos = std::stoi(argv[2]);
    } catch (...) {
        std::cerr << "Error: argumentos inválidos." << std::endl;
        return 1;
    }

    // Inicializa el generador de números aleatorios
    srand(time(0));

    // Almacena el lugar de llegada para cada auto
    int lugarLlegada = 0;
    std::vector<int> posiciones(numAutos, 0);

    // Crea un vector para las hebras de los autos
    std::vector<std::thread> autos;
    
    // Crea y lanza una hebra por cada auto
    for (int i = 0; i < numAutos; ++i) {
        autos.push_back(std::thread(correrAuto, i, distanciaTotal, std::ref(lugarLlegada), std::ref(posiciones)));
    }

    // Espera que todas las hebras terminen
    for (auto& autoThread : autos) {
        autoThread.join();
    }

    // Muestra el resultado final de la carrera
    std::cout << "Lugar  | Auto" << std::endl;
    std::cout << "-------|------" << std::endl;
    for (int i = 1; i <= numAutos; ++i) {
        for (int j = 0; j < numAutos; ++j) {
            if (posiciones[j] == i) {
                std::cout << "   " << i << "   | Auto" << j << std::endl;
            }
        }
    }

    return 0;
}
