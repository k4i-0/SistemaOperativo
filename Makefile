# Nombre del ejecutable
TARGET = carrera

# Compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -pthread

# Archivos fuente
SRCS = carrera.cpp

# Objetos
OBJS = $(SRCS:.cpp=.o)

# Regla principal: compilar
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar los archivos .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJS) $(TARGET)
