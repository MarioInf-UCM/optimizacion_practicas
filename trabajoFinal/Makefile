CC = mpic++
CFLAGS = -std=c++11 
LIBS = -ljsoncpp
BIN_DIR = bin
OUT_DIR = out
TARGET = trabajoFinal_exec
numProc = 2	 	#Portatil
#numProc = 4	#Sobremesa
configFileURL = /home/mario/Documentos/universidad/optimizacion/optimizacion_practicas/trabajoFinal/docs/config.json	#Portatil
#configFileURL = /home/mario/Documentos/universidad/optimizacion_practicas/trabajoFinal/docs/config.json				#Sobremesa

OBJS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SRCS))

#Incluimos la clase Main
SRCS += src/main.cpp

#Referencia a los elementos del directorio src/Interface
SRCS += src/interface/Json_interface/Json_interface.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/JsonConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/ComputerConfiguration/ComputerConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/RankConfiguration/RankConfiguration.cpp
SRCS += src/interface/Json_interface/JsonConfiguration/WorldConfiguration/WorldConfiguration.cpp
SRCS += src/interface/FileWriter_interface/FileWriter_interface.cpp

#Referencia a los elementos del directorio src/FitnessFunction
SRCS += src/FitnessFunction/FitnessFunction.cpp
SRCS += src/FitnessFunction/FitnessFunction_Pow2/FitnessFunction_Pow2.cpp

#Referencia a los elementos del directorio src/Heuristic
SRCS += src/Heuristic/Heuristic.cpp
SRCS += src/Heuristic/Heuristic_ArtificialBeeColony/Heuristic_ArtificialBeeColony.cpp
SRCS += src/Heuristic/Heuristic_DifferentialEvolution/Heuristic_DifferentialEvolution.cpp
SRCS += src/Heuristic/Heuristic_Fireworks/Heuristic_Fireworks.cpp
SRCS += src/Heuristic/Heuristic_ParticleSwarmOptimization/Heuristic_ParticleSwarmOptimization.cpp



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN_DIR)/$(TARGET) $(LIBS)

$(BIN_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@



run: $(TARGET)
	mpirun -n $(numProc) ./$(BIN_DIR)/$(TARGET) $(configFileURL)

clear:
	rm -rf $(BIN_DIR) $(TARGET)

clearOutPut:
	rm -rf $(OUT_DIR)/*

plot:
	gnuplot src/GnuPlot_scripts/examplePlot.gp