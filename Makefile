# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -pthread

# Archivo ejecutable
EXEC = carrera

# Archivos fuente
SRC = carrera.cpp

# Regla principal para compilar
all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Limpia los archivos generados
clean:
	rm -f $(EXEC)
