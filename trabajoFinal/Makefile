CC = mpic++
CFLAGS = -std=c++11

TARGET = src/mpi_exc
numProc = 2

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o $(TARGET)

run: $(TARGET)
	mpirun -n $(numProc) ./$(TARGET)

clean:
	rm -f $(TARGET)
