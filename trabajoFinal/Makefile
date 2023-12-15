CC = mpic++
CFLAGS = -std=c++11
OUT_DIR = bin
TARGET = trabajoFinal_exec
numProc = 2

OBJS = $(patsubst %.cpp,$(OUT_DIR)/%.o,$(SRCS))
SRCS += src/main.cpp
SRCS += src/world/world.cpp
SRCS += libs/arrayList/arrayList.cpp
SRCS += libs/fitnessFunctions/fitnessFunctions.cpp
SRCS += libs/heuristics/heuristics.cpp



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT_DIR)/$(TARGET)

$(OUT_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@



run: $(TARGET)
	mpirun -n $(numProc) ./$(OUT_DIR)/$(TARGET)



clean:
	rm -rf $(OUT_DIR) $(TARGET)





