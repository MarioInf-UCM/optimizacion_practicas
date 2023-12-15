#include <iostream>
#include <mpi.h>

#include "world/world.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        std::cerr << "Se necesitan al menos dos procesos para este ejemplo." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int messageTag = 0;
    const int dataSize = 1;

    if (rank == 0) {
        int sendData = 42;

        // Proceso 0 envía datos al Proceso 1
        MPI_Send(&sendData, dataSize, MPI_INT, 1, messageTag, MPI_COMM_WORLD);
        std::cout << "Proceso 0 envió el dato " << sendData << " al Proceso 1." << std::endl;
    } else if (rank == 1) {
        int receiveData;

        // Proceso 1 recibe datos del Proceso 0
        MPI_Recv(&receiveData, dataSize, MPI_INT, 0, messageTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Proceso 1 recibió el dato " << receiveData << " del Proceso 0." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
