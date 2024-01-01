CC = mpic++
CFLAGS = -std=c++11 
LIBS = -ljsoncpp
OUT_DIR = bin
TARGET = trabajoFinal_exec
numProc = 2
#configFileURL = /home/mario/Documentos/universidad/optimizacion/optimizacion_practicas/trabajoFinal/docs/config.json
configFileURL = /home/mario/Documentos/universidad/optimizacion_practicas/trabajoFinal/docs/config.json

OBJS = $(patsubst %.cpp,$(OUT_DIR)/%.o,$(SRCS))

#Incluimos la clase Main
SRCS += src/main.cpp

#Incluimos la clase World
SRCS += src/World/World.cpp

#Referencia a los elementos del directorio Interface
SRCS += src/interface/Json_interface/Json_interface.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/JsonConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/ComputerConfiguration/ComputerConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/RankConfiguration/RankConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/WorldConfiguration/WorldConfiguration.cpp

#Referencia a los elementos del directorio libs
SRCS += libs/ArrayList/ArrayList.cpp



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT_DIR)/$(TARGET) $(LIBS)

$(OUT_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@



run: $(TARGET)
	mpirun -n $(numProc) ./$(OUT_DIR)/$(TARGET) $(configFileURL)



clean:
	rm -rf $(OUT_DIR) $(TARGET)





