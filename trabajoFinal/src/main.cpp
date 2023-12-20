#include <iostream>
#include <mpi.h>

#include "World/World.h"
#include "interface/Json_interface/Json_interface.h"
#include "interface/Json_interface/JsonConfiguration/JsonConfiguration.h"

#define ENTRY_PARAM_NUM 2
bool entryParams_check(int argc, char** argv);

using namespace std;

int main(int argc, char** argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        if(!entryParams_check(argc, argv)){
            cerr << "FINALIZANDO PROGRAMA" << endl;
            MPI_Finalize();
            return -1;
        }
        Json_interface json_interface = Json_interface(argv[1]);
        JsonConfiguration jsonConfiguration = json_interface.getJSONConfiguration_FromFile();
        cout << jsonConfiguration.displayInfo() << endl;


    }
    









/*  
    if (size < 2) {
        cerr << "Se necesitan al menos dos procesos para este ejemplo." << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    const int messageTag = 0;
    const int dataSize = 1;

    if (rank == 0) {
        int sendData = 42;

        // Proceso 0 envía datos al Proceso 1
        MPI_Send(&sendData, dataSize, MPI_INT, 1, messageTag, MPI_COMM_WORLD);
        cout << "Proceso " << rank << "/" << size << " envió el dato " << sendData << " al Proceso 1." << endl;
    } else if (rank == 1) {
        int receiveData;

        // Proceso 1 recibe datos del Proceso 0
        MPI_Recv(&receiveData, dataSize, MPI_INT, 0, messageTag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Proceso " << rank << "/" << size << " recibió el dato " << receiveData << " del Proceso 0." << endl;
    }
 */
    MPI_Finalize();
    return 0;
}



bool entryParams_check(int argc, char** argv){

    if(argc != ENTRY_PARAM_NUM){
        cerr << "Parámetros de entrada  incorrectos. Se esperaban "<< ENTRY_PARAM_NUM << ", se han registrado " << argc << endl;
        cerr << "Ejemplo de ejecución: mpirun -n \"numProcesos\" program \"configFileURL\"" << endl;
        return false;
    }else{
        cout << endl;
        cout << "************************************************" << endl;
        cout << "EJECUCIÓN DE ALGORITMOS HEURíSTICOS DISTRIBUIDOS" << endl;
        cout << "************************************************" << endl;
        cout << endl;

        cout << "Ejecución iniciada con éxito." << endl;
        cout << "Parámetros iniciales:" << endl;
        cout << "\tFichero de configuración:" << argv[1] << endl;
        cout << endl;
        cout << "*************************************************************************" << endl;
        cout << endl;

    }
    return true;
}
