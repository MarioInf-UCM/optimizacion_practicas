#include <iostream>
#include <mpi.h>

#include "world/world.h"
#include "interface/json_interface/json_interface.h"

#define ENTRY_PARAM_NUM 1
bool entryParams_check(int argc, char** argv);


int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        if(!entryParams_check(argc, argv)){
            std::cerr << "FINALIZANDO PROGRAMA" << std::endl;
            MPI_Finalize();
            return -1;
        }
        Json_interface json_interface = Json_interface(argv[0]);

    }
    









/*  
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
        std::cout << "Proceso " << rank << "/" << size << " envió el dato " << sendData << " al Proceso 1." << std::endl;
    } else if (rank == 1) {
        int receiveData;

        // Proceso 1 recibe datos del Proceso 0
        MPI_Recv(&receiveData, dataSize, MPI_INT, 0, messageTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Proceso " << rank << "/" << size << " recibió el dato " << receiveData << " del Proceso 0." << std::endl;
    }
 */
    MPI_Finalize();
    return 0;
}



bool entryParams_check(int argc, char** argv){

    if(argc != ENTRY_PARAM_NUM){
        std::cerr << "Parámetros de entrada  incorrectos. Se esperaban "<< ENTRY_PARAM_NUM << ", se han registrado " << argc << std::endl;
        std::cerr << "Ejemplo de ejecución: mpirun -n \"numProcesos\" program \"configFileURL\"" << std::endl;
        return false;
    }else{
        std::cerr << std::endl;
        std::cerr << "Ejecución iniciada con éxito." << std::endl;
        std::cerr << "Parámetros iniciales:" << std::endl;
        std::cerr << "\tFichero de configuración:" << argv[0] << std::endl;

    }
    return true;
}
