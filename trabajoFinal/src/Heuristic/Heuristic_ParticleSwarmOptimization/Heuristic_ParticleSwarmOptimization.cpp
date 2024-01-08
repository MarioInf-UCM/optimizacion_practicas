#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>
#include "Heuristic_ParticleSwarmOptimization.h"

#define MAX_VELOCITY_PERCENTAGE 10
#define DEPURE_MESSAGES_FLAG false
#define SHARED_THRESHOLD_PERCENTAGE 0.1 //(0-1)
#define PRINT_STATUS_CYCLICAL 100
#define SEPARATOR " "

using namespace std;

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_ParticleSwarmOptimization::Heuristic_ParticleSwarmOptimization():
    Heuristic("ParticleSwarmOptimization")
{}

Heuristic_ParticleSwarmOptimization::~Heuristic_ParticleSwarmOptimization(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************

bool Heuristic_ParticleSwarmOptimization::execHeuristic(float (*fitnessFunction)(float), WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    srand(static_cast<unsigned int>(time(0)));
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);

    unsigned int dimensions = rankConfiguration.getDimensions();
    unsigned int iterations = rankConfiguration.getIterations();
    unsigned int poblation = rankConfiguration.getPoblation();
    float inertiaFactor = rankConfiguration.getValue_byIndex(0);
    float personalFactor = rankConfiguration.getValue_byIndex(1);
    float grupalFactor = rankConfiguration.getValue_byIndex(2);
    float maxVelocity_AbsoluteValor = fabs(worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft());

    double newVelocity = 0.0;
    double newPosition = 0.0;
    double resultFitness_actualposition = 0.0;
    double resultFitness_bestPositionPersonal = 0.0;
    double resultFitness_bestPositionGlobal = 0.0;
    double posTemp = 0.0;
    int lastIteration = 0;
    bool flagEnd = false;
    float minShared = 0.0;

    
    vector<float> minPosList = vector<float>();
    for(int i=0 ; i<dimensions ; i++){
        minPosList.push_back(  worldConfiguration.getLimitLeft() + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft()))) );
    }
    vector<vector<float>> actualVelocityList = vector<vector<float>>();
    vector<vector<float>> actualPositionList = vector<vector<float>>();
    vector<vector<float>> bestPositionPersonalList = vector<vector<float>>();
    vector<float> velocityVectorTemp, positionVectorTemp, bestPositionPersonalVectorTemp;
    for(int i=0 ; i<poblation ; i++){
        velocityVectorTemp = vector<float>();
        positionVectorTemp = vector<float>();
        bestPositionPersonalVectorTemp = vector<float>();

        for(int j=0 ; j<dimensions; j++){
            velocityVectorTemp.push_back(generarNumeroAleatorio(worldConfiguration.getLimitLeft(), worldConfiguration.getLimitRight()));
            positionVectorTemp.push_back(generarNumeroAleatorio(maxVelocity_AbsoluteValor, -maxVelocity_AbsoluteValor));
            bestPositionPersonalVectorTemp.push_back(positionVectorTemp.back());
        }
        actualVelocityList.push_back(velocityVectorTemp);
        actualPositionList.push_back(positionVectorTemp);
        bestPositionPersonalList.push_back(bestPositionPersonalVectorTemp);
    }


    for (int iteration = lastIteration; iteration < iterations; iteration++) {

        // Paso 1: Actualización del vector de velocidades por cada partícula
        for (int particle = 0; particle < poblation; particle++) {
            for (int dimension = 0; dimension < dimensions; dimension++) {

                newVelocity = inertiaFactor * actualVelocityList[particle][dimension];
                newVelocity = newVelocity + (personalFactor * generarNumeroAleatorio(0, 1) * (bestPositionPersonalList[particle][dimension] - actualPositionList[particle][dimension]));
                newVelocity = newVelocity + (grupalFactor * generarNumeroAleatorio(0, 1) * (minPosList[dimension]- actualPositionList[particle][dimension]));

                if(newVelocity > maxVelocity_AbsoluteValor){
                    newVelocity = maxVelocity_AbsoluteValor;
                }else if(newVelocity < -maxVelocity_AbsoluteValor){
                    newVelocity = -maxVelocity_AbsoluteValor;
                }
                actualVelocityList[particle][dimension]=newVelocity;
            }
        }

        // Paso 2: Actualización del vector de posición por cada partícula
        for (int particle = 0; particle < poblation; particle++) {
            for (int dimension = 0; dimension < dimensions; dimension++) {

                newPosition = actualPositionList[particle][dimension] + actualVelocityList[particle][dimension];   
                if (newPosition < worldConfiguration.getLimitLeft()) {
                    newPosition = worldConfiguration.getLimitLeft();
                } else if (newPosition > worldConfiguration.getLimitRight()) {
                    newPosition = worldConfiguration.getLimitLeft();
                }
                actualPositionList[particle][dimension] = newPosition;
            }
        }

        // Paso 3: Actualización de los minimos locales y globales
        for (int particle = 0; particle < poblation; particle++) {
            for (int dimension = 0; dimension < dimensions; dimension++) {

                posTemp = actualPositionList[particle][dimension];
                resultFitness_actualposition = fitnessFunction((double)posTemp);
 
                resultFitness_bestPositionPersonal = fitnessFunction(bestPositionPersonalList[particle][dimension]);
                resultFitness_bestPositionGlobal = fitnessFunction(minPosList[dimension]);

                if (resultFitness_actualposition < resultFitness_bestPositionPersonal) {
                    bestPositionPersonalList[particle][dimension]= posTemp;
                }
                if (resultFitness_actualposition < resultFitness_bestPositionGlobal) {
                    minPosList[dimension]=posTemp;

                    //Compartimos el nuevo mínimo
                    checkAndSendMinimun(posTemp, resultFitness_bestPositionGlobal, resultFitness_actualposition, file_commonLog, file_resultCSV);

                }
                
            }
        }

        //Paso 4: Comprobamos los mínimos recibidos
        if(checkAndReciveMinimun(&minShared, file_commonLog, file_resultCSV, flagVerbose)){
            for(int dimension=0 ; dimension<dimensions ; dimension++){
                if(fitnessFunction(minShared) < fitnessFunction(minPosList[dimension])){
                    minPosList[dimension] = minShared;
                    printStream <<"Proceso: " << rank << " - Iteración: " << iteration << " Posición " << minShared << "compartida, aceptada como nuevo mínimo de la dimension: " << dimension;
                    file_commonLog.writeln(printStream, flagVerbose);
                }
            }
        }

        if(DEPURE_MESSAGES_FLAG){
            printStream <<"Proceso: " << rank << " - Iteración: " << iteration << " Posición actual{";
            for (int particle = 0; particle < poblation; particle++) {
                printStream <<"[ ";
                for (int dimension = 0; dimension < dimensions; dimension++) {
                    printStream << actualPositionList[particle][dimension] << " "; 
                }
                printStream <<"]";
            }
            printStream <<"} Velocidad actual:{";
            for (int particle = 0; particle < poblation; particle++) {
                printStream <<"[ ";
                for (int dimension = 0; dimension < dimensions; dimension++) {
                    printStream << actualVelocityList[particle][dimension] << " "; 
                }
                printStream <<"]";
            }
            printStream <<"} Mejores mínimos personales:{";
            for (int particle = 0; particle < poblation; particle++) {
                printStream <<"[ ";
                for (int dimension = 0; dimension < dimensions; dimension++) {
                    printStream << bestPositionPersonalList[particle][dimension] << " "; 
                }
                printStream <<"]";
            }
            printStream <<" Mínimos globales:[";
            for(int i=0 ; i<minPosList.size() ; i++){
                printStream << minPosList[i] << " ";
            }
            printStream << "]";
            file_commonLog.writeln(printStream, flagVerbose);
        }else if(iteration%PRINT_STATUS_CYCLICAL == 0){
            printStream <<"Proceso: " << rank << " - Iteración: " << iteration << " Mínimos globales[";
            for(int i=0 ; i<minPosList.size() ; i++){
                printStream << minPosList[i] << " ";
            }
            printStream << "]";
            file_commonLog.writeln(printStream, flagVerbose);
        }

    }
    
    return true;
}


double Heuristic_ParticleSwarmOptimization::generarNumeroAleatorio(double minimo, double maximo) {
    double numeroAleatorio = minimo + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (maximo - minimo)));
    return numeroAleatorio;
}


void Heuristic_ParticleSwarmOptimization::checkAndSendMinimun(float posTemp, float oldMin, float newMin, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){

    ostringstream printStream;
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    if(newMin < oldMin - (oldMin*SHARED_THRESHOLD_PERCENTAGE)){

        for (int destino = 0; destino < size; ++destino) {
            if (destino != rank) {
                MPI_Send(&posTemp, 1, MPI_FLOAT, destino, 0, MPI_COMM_WORLD);
            }
        }
        printStream << "Proceso: " << rank << " - Nuevo mínimo comparido{ x:" << posTemp << " y:" << oldMin << "}";
        file_commonLog.writeln(printStream, flagVerbose);
        printStream << getID() << SEPARATOR << posTemp << SEPARATOR << newMin;
        file_resultCSV.writeln(printStream, flagVerbose);

    }
    return;
}

bool Heuristic_ParticleSwarmOptimization::checkAndReciveMinimun(float *data,  FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    ostringstream printStream;
    MPI_Status statusMessage;
    int rank, size, result, numMessages;
    float receivedData = FLT_MAX;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    result = MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &numMessages, &statusMessage);
    if(result != MPI_SUCCESS){
        printStream << "Proceso: " << rank << "Error en la comprobación de mensajes pendientes{ fuente: " << statusMessage.MPI_SOURCE << " errorCode:"  << statusMessage.MPI_ERROR << "}" ; file_commonLog.writeln(printStream, flagVerbose);

    }else if(numMessages>0){
        result != MPI_Recv(&receivedData, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &statusMessage);
        if(result != MPI_SUCCESS){
            printStream << "Proceso: " << rank << "Error en la recepción de mensajes{ fuente: " << statusMessage.MPI_SOURCE << " errorCode:"  << statusMessage.MPI_ERROR << "}" ; file_commonLog.writeln(printStream, flagVerbose);
        }else{
            printStream << "Proceso: " << rank << " - Nuevo mínimo recibido{ fuente: " << statusMessage.MPI_SOURCE << " x: " << receivedData << "}"; file_commonLog.writeln(printStream, flagVerbose);
            if(receivedData < *data){
                *data = receivedData;
            }
            return true;
        }
    }
    return false;
}