#include <iostream>
#include <mpi.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <ifaddrs.h>


#include "interface/Json_interface/Json_interface.h"
#include "interface/Json_interface/JsonConfiguration/JsonConfiguration.h"
#include "interface/FileWriter_interface/FileWriter_interface.h"
#include "Heuristic/Heuristic_ArtificialBeeColony/Heuristic_ArtificialBeeColony.h"
#include "Heuristic/Heuristic_DifferentialEvolution/Heuristic_DifferentialEvolution.h"
#include "Heuristic/Heuristic_Fireworks/Heuristic_Fireworks.h"
#include "Heuristic/Heuristic_ParticleSwarmOptimization/Heuristic_ParticleSwarmOptimization.h"
#include "FitnessFunction/FitnessFunction_Pow2/FitnessFunction_Pow2.h"
#include "FitnessFunction/FitnessFunction_num8/FitnessFunction_num8.h"

#define ROOT 0
#define ENTRY_PARAM_NUM 2
#define VERBOSE true
#define IPV4_DEFAULT "0.0.0.0"
#define IPV6_DEFAULT "::0"

bool entryParams_check(int argc, char** argv);
void print_entryParams(int argc, char** argv, FileWriter_interface& fileOutPut, bool printInfo);
bool getIPDirections_UNIX(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, vector<string>& IPv4Ifaces, vector<string>& IPv6Ifaces);
void print_IPdirections(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, vector<string>& IPv4Ifaces, vector<string>& IPv6Ifaces, FileWriter_interface& fileOutPut, bool printInfo = true);
bool checkRankInList(vector<unsigned int> vector, unsigned int rank);
bool FinalizingExecution(MPI_Comm *CommComputer, bool abort=false);

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    JsonConfiguration jsonConfiguration;
    vector<string> ipv4Addresses, IPv4Ifaces;
    vector<string> ipv6Addresses, IPv6Ifaces;
    RankConfiguration configRank;
    FileWriter_interface file_commonLog;
    FileWriter_interface outPutFile;
    
    ostringstream printStream;
    int result, errorStringLen;
    bool flag = true;
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
        if(!entryParams_check(argc, argv)){
            cerr << "Error en los parámetros de entrada." << endl;
            flag=false;
        }
        if(!getIPDirections_UNIX(ipv4Addresses, ipv6Addresses, IPv4Ifaces, IPv6Ifaces)) {
            cerr << "Error al obtener direcciones IP." << endl;
            flag=false;
        }

        if(flag){
            Json_interface json_interface = Json_interface(argv[1]);
            jsonConfiguration = json_interface.getJSONConfiguration_FromFile(ipv4Addresses, ipv6Addresses);
            file_commonLog.setFileURL(jsonConfiguration.getComputerConfiguration().getLogCommonFile());

            printStream << "************************************************"; file_commonLog.writeln(printStream, VERBOSE);
            printStream << "EJECUCIÓN DE ALGORITMOS HEURÍSTICOS DISTRIBUIDOS"; file_commonLog.writeln(printStream, VERBOSE);
            printStream << "************************************************"; file_commonLog.writeln(printStream, VERBOSE);
            print_entryParams(argc, argv, file_commonLog, VERBOSE);
            print_IPdirections(ipv4Addresses, ipv6Addresses, IPv4Ifaces, IPv6Ifaces, file_commonLog, VERBOSE);
            printStream << endl << "Fichero de configuración..:" << endl << jsonConfiguration.displayInfo(); file_commonLog.writeln(printStream, VERBOSE);
            printStream << "*************************************************************************" << endl; file_commonLog.writeln(printStream, VERBOSE);
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

        if(!getIPDirections_UNIX(ipv4Addresses, ipv6Addresses, IPv4Ifaces, IPv6Ifaces)) {
            cerr << "Error al obtener direcciones IP." << endl;
            cerr << "FINALIZANDO PROGRAMA" << endl;
            FinalizingExecution(&CommComputer);
            return 1;
        }
        Json_interface json_interface = Json_interface(argv[1]);
        jsonConfiguration = json_interface.getJSONConfiguration_FromFile(ipv4Addresses, ipv6Addresses);
        file_commonLog.setFileURL(jsonConfiguration.getComputerConfiguration().getLogCommonFile());
    }

    result = false;
    for(int i=0 ; i<jsonConfiguration.getComputerConfiguration().getRankConfigurationList().size() ; i++){
        if(checkRankInList(jsonConfiguration.getComputerConfiguration().getRankConfiguration_byIndex(i).getRankList(), rank)){
            configRank = jsonConfiguration.getComputerConfiguration().getRankConfiguration_byIndex(i);
            outPutFile.setFileURL(configRank.getOutputFile());
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

    float (*FitnessFunction)(float);
    FitnessFunction_Pow2 fitnessFunction_Pow2 = FitnessFunction_Pow2();
    FitnessFunction_num8 fitnessFunction_num8 = FitnessFunction_num8();
    if(!jsonConfiguration.getWorldConfiguration().getFitnessFunctionID().compare(fitnessFunction_Pow2.getID())){
        FitnessFunction = FitnessFunction_Pow2::execFunction;
    }else if(!jsonConfiguration.getWorldConfiguration().getFitnessFunctionID().compare(fitnessFunction_num8.getID())){
        FitnessFunction = FitnessFunction_num8::execFunction;
    }else{
        printStream << "Proceso " << rank << " - No se ha podido identificar la función de fitness correctamente (" << jsonConfiguration.getWorldConfiguration().getFitnessFunctionID() << ")"; file_commonLog.writeln(printStream, VERBOSE);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    Heuristic_ArtificialBeeColony heuristic_ArtificialBeeColony = Heuristic_ArtificialBeeColony();
    Heuristic_DifferentialEvolution heuristic_DifferentialEvolution = Heuristic_DifferentialEvolution();
    Heuristic_Fireworks heuristic_Fireworks = Heuristic_Fireworks();
    Heuristic_ParticleSwarmOptimization heuristic_ParticleSwarmOptimization = Heuristic_ParticleSwarmOptimization();
    printStream << "Proceso " << rank << " - Configuración{" << configRank.displayInfo() << "}"; file_commonLog.writeln(printStream, VERBOSE);

    if(!configRank.getHeuristicID().compare(heuristic_ArtificialBeeColony.getID())){
        result = heuristic_ArtificialBeeColony.execHeuristic(FitnessFunction, jsonConfiguration.getWorldConfiguration(), configRank, file_commonLog, outPutFile);

    }else if(!configRank.getHeuristicID().compare(heuristic_DifferentialEvolution.getID())){
        result = heuristic_DifferentialEvolution.execHeuristic(FitnessFunction, jsonConfiguration.getWorldConfiguration(), configRank, file_commonLog, outPutFile);

    }else if(!configRank.getHeuristicID().compare(heuristic_Fireworks.getID())){
        result = heuristic_Fireworks.execHeuristic(FitnessFunction, jsonConfiguration.getWorldConfiguration(), configRank, file_commonLog, outPutFile);

    }else if(!configRank.getHeuristicID().compare(heuristic_ParticleSwarmOptimization.getID())){
        result = heuristic_ParticleSwarmOptimization.execHeuristic(FitnessFunction, jsonConfiguration.getWorldConfiguration(), configRank, file_commonLog, outPutFile);
    }
    printStream << "proceso:" << rank << " - Ejecución finalizada"; file_commonLog.writeln(printStream, VERBOSE);


    FinalizingExecution(&CommComputer);
    return 0;
}



bool entryParams_check(int argc, char** argv){
    if(argc != ENTRY_PARAM_NUM){
        cerr << "Parámetros de entrada incorrectos. Se esperaban "<< ENTRY_PARAM_NUM << ", se han registrado " << argc << endl;
        cerr << "Ejemplo de ejecución: mpirun -n \"numProcesos\" program \"configFileURL\"" << endl;
        return false;
    }
    return true;
}


void print_entryParams(int argc, char** argv, FileWriter_interface& fileOutPut, bool printInfo){
    ostringstream printStream;
    if(printInfo){
        printStream << endl << "Parámetros iniciales:"; fileOutPut.writeln(printStream, printInfo);
        printStream << "\tFichero de configuración:" << argv[1]; fileOutPut.writeln(printStream, printInfo);
    }
    return;
}


bool getIPDirections_UNIX(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, vector<string>& IPv4Ifaces, vector<string>& IPv6Ifaces){
    struct ifaddrs *ifAddrStruct = nullptr;
    struct ifaddrs *ifa = nullptr;

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

    return true;
}


void print_IPdirections(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses, vector<string>& IPv4Ifaces, vector<string>& IPv6Ifaces, FileWriter_interface& fileOutPut, bool printInfo){
    ostringstream printStream;

    printStream << endl << "Direcciones IPv4:"; fileOutPut.writeln(printStream, printInfo);
    for (size_t i = 0; i < ipv4Addresses.size(); ++i) {
        printStream << "\tInterfaz: " << IPv4Ifaces[i] << "\t\tDirección: " << ipv4Addresses[i]; fileOutPut.writeln(printStream, printInfo);
    }
    printStream << endl << "Direcciones IPv6:"; fileOutPut.writeln(printStream, printInfo);
    for (size_t i = 0; i < ipv6Addresses.size(); ++i) {
        printStream << "\tInterfaz: " << IPv6Ifaces[i] << "\t\tDirección: " << ipv6Addresses[i]; fileOutPut.writeln(printStream, printInfo);
    }
    return;
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