# Simulador de Carrera de Autos

Este proyecto simula una carrera de autos utilizando programación multihebras en C++. Cada automóvil corre en una hebra separada y la distancia que avanza, así como su velocidad, es aleatoria.

## Requisitos

- Sistema operativo: Linux
- Compilador: GNU `g++` (C++11 o superior)
- Biblioteca estándar de C++ (thread)

## Compilar y ejecutar el programa

### Compilación

Este proyecto incluye un archivo `Makefile` para facilitar la compilación. Para compilar el programa, sigue estos pasos:

1. Asegúrate de estar en el directorio del proyecto donde están los archivos `Makefile` y `carrera.cpp`.
   
2. Ejecuta el siguiente comando en la terminal:

```
make
```
Esto generará el archivo ejecutable carrera.

Ejecución
Para ejecutar el programa, puedes usar el siguiente comando:

   ```
   ./carrera <distancia_total> <numero_de_autos>
   ```


Donde:

<distancia_total> es la distancia en metros que los autos deben recorrer.
<numero_de_autos> es la cantidad de autos que participarán en la carrera.

Ejemplo:
Si deseas simular una carrera de 100 metros con 3 autos, ejecuta:


   ```
   ./carrera 100 3
   ```



## Autores

-Cristian Oñate

-Guido Montecinos
