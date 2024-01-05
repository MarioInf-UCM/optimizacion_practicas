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
#include "interface/FileWriter_interface/FileWriter_interface.h"

#define ROOT 0
#define ENTRY_PARAM_NUM 2
#define IPV4_DEFAULT "0.0.0.0"
#define IPV6_DEFAULT "::0"

bool entryParams_check(int argc, char** argv, bool printInfo = true);
bool getIPDirections_UNIX(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, bool printInfo = true);
bool checkRankInList(vector<unsigned int> vector, unsigned int rank);
bool FinalizingExecution(MPI_Comm *CommComputer, bool abort=false);

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    JsonConfiguration jsonConfiguration;
    vector<string> ipv4Addresses;
    vector<string> ipv6Addresses;
    RankConfiguration configRank;
    FileWriter_interface logCommonFile;
    FileWriter_interface outPutFile;
    
    int result, errorStringLen;
    char errorString[MPI_MAX_ERROR_STRING];
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int node, CommComputer_size;
    MPI_Comm CommComputer;
    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, rank, MPI_INFO_NULL, &CommComputer);
    MPI_Comm_rank(CommComputer, &node);
    MPI_Comm_size(CommComputer, &CommComputer_size);


    if(rank == ROOT){
        cout << endl;
        cout << "************************************************" << endl;
        cout << "EJECUCIÓN DE ALGORITMOS HEURÍSTICOS DISTRIBUIDOS" << endl;
        cout << "************************************************" << endl;
        cout << endl;

        bool flag = true;
        if(!entryParams_check(argc, argv)){
            cerr << "Error en los parámetros de entrada." << endl;
            flag=false;
        }
        if(!getIPDirections_UNIX(ipv4Addresses, ipv6Addresses)) {
            cerr << "Error al obtener direcciones IP." << endl;
            flag=false;
        }

        if(flag){
            Json_interface json_interface = Json_interface(argv[1]);
            jsonConfiguration = json_interface.getJSONConfiguration_FromFile(ipv4Addresses, ipv6Addresses);
            logCommonFile.setFileURL(jsonConfiguration.getComputerConfiguration().getLogCommonFile());

            cout << endl << endl << "Fichero de configuración..:" << endl << endl;
            cout <<  jsonConfiguration.displayInfo();

            cout << endl;
            cout << "*************************************************************************" << endl;
            cout << endl;
        }
    
        for (int dest = 1; dest < size; ++dest) {
            int send_status = MPI_Send(&flag, 1, MPI_CXX_BOOL, dest, 0, MPI_COMM_WORLD);
            if (send_status != MPI_SUCCESS) {
                std::cerr << "Error al enviar datos desde el proceso 0 al proceso " << dest << std::endl;
                MPI_Abort(MPI_COMM_WORLD, 1);
            }
        }

        if(!flag){
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution(&CommComputer);
        }

    }else{      

        bool flag;
        result = MPI_Recv(&flag, 1, MPI_CXX_BOOL, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (result != MPI_SUCCESS) {
            cerr << "Error al recibir datos en el proceso " << rank << " desde el proceso 0" << endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }else if(!flag){
            FinalizingExecution(&CommComputer);
            return 1;            
        }

        if(!entryParams_check(argc, argv, false)){
            cerr << "Error en los parámetros de entrada." << endl;
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution(&CommComputer);
            return 1;
        }
        if(!getIPDirections_UNIX(ipv4Addresses, ipv6Addresses, false)) {
            cerr << "Error al obtener direcciones IP." << endl;
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution(&CommComputer);
            return 1;
        }
        Json_interface json_interface = Json_interface(argv[1]);
        jsonConfiguration = json_interface.getJSONConfiguration_FromFile(ipv4Addresses, ipv6Addresses);
    }

    result = false;
    for(int i=0 ; i<jsonConfiguration.getComputerConfiguration().getRankConfigurationList().size() ; i++){
        if(checkRankInList(jsonConfiguration.getComputerConfiguration().getRankConfiguration_byIndex(i).getRankList(), rank)){
            configRank = jsonConfiguration.getComputerConfiguration().getRankConfiguration_byIndex(i);
            result = true;
            break;
        }
    }
    if(!result){
        cerr << "No se ha encontrado una configuración válida pra el proceso " << rank << endl;
        cerr << "FINALIZANDO PROGRAMA" << endl;
        FinalizingExecution(&CommComputer);
        return 1;        
    }


    cout << "Configuración proceso " << rank << " :" << configRank.displayInfo() << endl; 





    FinalizingExecution(&CommComputer);
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



bool getIPDirections_UNIX(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, bool printInfo) {
    struct ifaddrs *ifAddrStruct = nullptr;
    struct ifaddrs *ifa = nullptr;
    vector<string> IPv4Ifaces;
    vector<string> IPv6Ifaces;

    if(getifaddrs(&ifAddrStruct) == -1) {
        cerr << "Error al obtener la información de las interfaces de red." << endl;
        return false;
    }

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
    }
    ipv4Addresses.push_back(IPV4_DEFAULT);
    IPv4Ifaces.push_back("Default");
    ipv6Addresses.push_back(IPV6_DEFAULT);
    IPv6Ifaces.push_back("Default");


    if(ifAddrStruct != nullptr) {
        freeifaddrs(ifAddrStruct);
    }
    if(printInfo){
        cout << "Direcciones IPv4:" << endl;
        for (size_t i = 0; i < ipv4Addresses.size(); ++i) {
            cout << "\tInterfaz: " << IPv4Ifaces[i] << "\t\tDirección: " << ipv4Addresses[i] << endl;
        }
        cout << "\nDirecciones IPv6:" << endl;
        for (size_t i = 0; i < ipv6Addresses.size(); ++i) {
            cout << "\tInterfaz: " << IPv6Ifaces[i] << "\t\tDirección: " << ipv6Addresses[i] << endl;
        }
    }

    return true;
}


bool checkRankInList(vector<unsigned int> vector, unsigned int rank){
    for(int i=0 ; i<vector.size() ; i++){
        if(vector[i] == rank){
            return true;
        }
    }
    return false;
}


bool FinalizingExecution(MPI_Comm *CommComputer, bool abort){
    bool result = true;
    if(MPI_Comm_free(CommComputer) != MPI_SUCCESS){
        result = false;
    };
    
    if(MPI_Finalize() != MPI_SUCCESS){
        result = false;
    }

    return result;
}