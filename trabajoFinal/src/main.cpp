#include <iostream>
#include <mpi.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

#include "World/World.h"
#include "interface/Json_interface/Json_interface.h"
#include "interface/Json_interface/JsonConfiguration/JsonConfiguration.h"
#include "../libs/ArrayList/ArrayList.h"

#define ENTRY_PARAM_NUM 2
bool entryParams_check(int argc, char** argv, bool printInfo = true);
bool getIPDirections_UNIX(std::vector<std::string>& ipv4Addresses, std::vector<std::string>& ipv6Addresses, bool printInfo = true);
bool FinalizingExecution();

using namespace std;

int main(int argc, char** argv) {

    std::vector<std::string> ipv4Addresses;
    std::vector<std::string> ipv6Addresses;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 


    if(rank == 0){
        cout << endl;
        cout << "************************************************" << endl;
        cout << "EJECUCIÓN DE ALGORITMOS HEURÍSTICOS DISTRIBUIDOS" << endl;
        cout << "************************************************" << endl;
        cout << endl;

        if(!entryParams_check(argc, argv)){
            std::cerr << "Error en los parámetros de entrada." << std::endl;
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution();
            return 1;
        }
        if(!getIPDirections_UNIX(ipv4Addresses, ipv6Addresses)) {
            std::cerr << "Error al obtener direcciones IP." << std::endl;
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution();
            return 1;
        }
        cout << endl;
        cout << "*************************************************************************" << endl;
        cout << endl;

        Json_interface json_interface = Json_interface(argv[1]);
        JsonConfiguration jsonConfiguration = json_interface.getJSONConfiguration_FromFile();
        cout <<  jsonConfiguration.displayInfo() << endl;
    }

    
    

/*




    if(rank == 0){
    
    }if (size < 2) {
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
    FinalizingExecution();
    return 0;
}



bool entryParams_check(int argc, char** argv, bool printInfo){

    if(argc != ENTRY_PARAM_NUM){
        cerr << "Parámetros de entrada incorrectos. Se esperaban "<< ENTRY_PARAM_NUM << ", se han registrado " << argc << endl;
        cerr << "Ejemplo de ejecución: mpirun -n \"numProcesos\" program \"configFileURL\"" << endl;
        return false;
    }else if(printInfo){
        cout << "Parámetros iniciales:" << endl;
        cout << "\tFichero de configuración:" << argv[1] << endl << endl;
    }
    return true;
}



bool getIPDirections_UNIX(std::vector<std::string>& ipv4Addresses, std::vector<std::string>& ipv6Addresses, bool printInfo) {
    struct ifaddrs *ifAddrStruct = nullptr;
    struct ifaddrs *ifa = nullptr;
    vector<string> IPv4Ifaces;
    vector<string> IPv6Ifaces;

    if(getifaddrs(&ifAddrStruct) == -1) {
        std::cerr << "Error al obtener la información de las interfaces de red." << std::endl;
        return false;
    }

    unsigned int pos=0;
    for(ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        void *addr;
        if (ifa->ifa_addr->sa_family == AF_INET) {
            addr = &reinterpret_cast<struct sockaddr_in*>(ifa->ifa_addr)->sin_addr;
            char ipstr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, addr, ipstr, sizeof(ipstr));
            ipv4Addresses.push_back(ipstr);
            IPv4Ifaces.push_back(string(ifa->ifa_name));
        } else if (ifa->ifa_addr->sa_family == AF_INET6) {
            addr = &reinterpret_cast<struct sockaddr_in6*>(ifa->ifa_addr)->sin6_addr;
            char ipstr[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, addr, ipstr, sizeof(ipstr));
            ipv6Addresses.push_back(ipstr);
            IPv6Ifaces.push_back(string(ifa->ifa_name));
        } else {
            continue;
        }
        pos++;
    }

    if(ifAddrStruct != nullptr) {
        freeifaddrs(ifAddrStruct);
    }
    if(printInfo){
        std::cout << "Direcciones IPv4:" << std::endl;
        for (size_t i = 0; i < ipv4Addresses.size(); ++i) {
            std::cout << "\tInterfaz: " << IPv4Ifaces[i] << "\tDirección IPv4: " << ipv4Addresses[i] << std::endl;
        }
        std::cout << "\nDirecciones IPv6:" << std::endl;
        for (size_t i = 0; i < ipv6Addresses.size(); ++i) {
            std::cout << "\tInterfaz: " << IPv6Ifaces[i] << "\tDirección IPv6: " << ipv6Addresses[i] << std::endl;
        }
    }

    return true;
}



bool FinalizingExecution(){
    bool result = true;
    if(MPI_Finalize() != MPI_SUCCESS){
        result = false;
    }
    return result;
}