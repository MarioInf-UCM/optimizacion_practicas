#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cfloat>

#include "Heuristic_DifferentialEvolution.h"

#define MAX_VELOCITY_PERCENTAGE 10
#define DEPURE_MESSAGES_FLAG false
#define SHARED_THRESHOLD_PERCENTAGE 0.1 //(0-1)
#define PRINT_STATUS_CYCLICAL 100
#define SEPARATOR " "


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_DifferentialEvolution::Heuristic_DifferentialEvolution():
    Heuristic("DifferentialEvolution")
{}

Heuristic_DifferentialEvolution::~Heuristic_DifferentialEvolution(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool Heuristic_DifferentialEvolution::execHeuristic(float (*fitnessFunction)(float), WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    srand(static_cast<unsigned int>(time(0)));
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);

        unsigned int dimensions = rankConfiguration.getDimensions();
        unsigned int iterations = rankConfiguration.getIterations();
        unsigned int poblation = rankConfiguration.getPoblation();
        float crossover = rankConfiguration.getValue_byIndex(0);
        float differentialWeight = rankConfiguration.getValue_byIndex(1);
        float maxVelocity_AbsoluteValor = fabs(worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft());

        int lastIteration = 0;
        bool flagEnd = false;
        int partSelected_1=0, indexSelected_1=0;
        int partSelected_2=0, indexSelected_2=0;
        int partSelected_3=0, indexSelected_3=0;
        int dimensionSelected=0;
        double newPosition = 0.0;
        float minShared = 0.0;


        vector<float> minPosList = vector<float>();
        for(int i=0 ; i<dimensions ; i++){
            minPosList.push_back(  worldConfiguration.getLimitLeft() + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft()))) );
        }
        vector<vector<float>> actualPositionList = vector<vector<float>>();
        vector<float> positionVectorTemp;
        vector<int>particleSelectorList = vector<int>();

        for(int i=0 ; i<poblation ; i++){
            positionVectorTemp = vector<float>();
            for(int j=0 ; j<dimensions; j++){
                positionVectorTemp.push_back(generarNumeroAleatorio(maxVelocity_AbsoluteValor, -maxVelocity_AbsoluteValor));
            }
            actualPositionList.push_back(positionVectorTemp);
            particleSelectorList.push_back(i);
        }

        for (int iteration = lastIteration; iteration < iterations; iteration++) {
            
            for (int particle = 0; particle < poblation; particle++) {
        
                // Paso 1: Seleccionamos las partículas y la dimension a operar
                indexSelected_1 = generarNumeroAleatorio(0, particleSelectorList.size());
                partSelected_1 = particleSelectorList[indexSelected_1];
                particleSelectorList.erase(particleSelectorList.begin() + indexSelected_1);

                indexSelected_2 = generarNumeroAleatorio(0, particleSelectorList.size());
                partSelected_2 = particleSelectorList[indexSelected_2];
                particleSelectorList.erase(particleSelectorList.begin() + indexSelected_2);

                indexSelected_3 = generarNumeroAleatorio(0, particleSelectorList.size());
                partSelected_3 = particleSelectorList[indexSelected_3];
                particleSelectorList.erase(particleSelectorList.begin() + indexSelected_3);

                particleSelectorList = vector<int>();
                for(int i=0 ; i<poblation ; i++){
                    particleSelectorList.push_back(i);
                }

                dimensionSelected = generarNumeroAleatorio(0, dimensions);


                // Paso 2: Modificamos la dimensión seleccionada
                newPosition = actualPositionList[partSelected_1][dimensionSelected] + differentialWeight * ( actualPositionList[partSelected_2][dimensionSelected] - actualPositionList[partSelected_3][dimensionSelected] );
                if(fitnessFunction(newPosition)<fitnessFunction(actualPositionList[particle][dimensionSelected])){
                    actualPositionList[particle][dimensionSelected] = newPosition;
                
                    if(fitnessFunction(newPosition)<fitnessFunction(minPosList[dimensionSelected])){
                        
                        //Compartimos el nuevo mínimo
                        checkAndSendMinimun(newPosition, fitnessFunction(minPosList[dimensionSelected]), fitnessFunction(newPosition), file_commonLog, file_resultCSV);
                        minPosList[dimensionSelected] = newPosition;
                    }
                }

                //Paso 3: Modificamos las dimensiones restantes
                for (int dimension = 0; dimension < dimensions; dimension++) {
                    if(dimension != dimensionSelected && generarNumeroAleatorio(0, 1)<crossover){
                        newPosition = actualPositionList[partSelected_1][dimensionSelected] + differentialWeight * ( actualPositionList[partSelected_2][dimensionSelected] - actualPositionList[partSelected_3][dimensionSelected] );
                    
                        if(fitnessFunction(newPosition)<fitnessFunction(actualPositionList[particle][dimension])){
                            actualPositionList[particle][dimension] = newPosition;
                        }
                        if(fitnessFunction(newPosition)<fitnessFunction(minPosList[dimension])){
                            minPosList[dimension]=newPosition;
                        }

                    }
                }

                //Paso 4: Comprobamos los mínimos recibidos
                if(checkAndReciveMinimun(&minShared, file_commonLog, file_resultCSV, flagVerbose)){
                    for(int dimension=0 ; dimension<dimensions ; dimension++){
                        if(fitnessFunction(minShared) < fitnessFunction(minPosList[dimension])){
                            minPosList[dimension] = minShared;
                            printStream <<"Proceso: " << rank << " - Iteración: " << iteration << " Posición " << minShared << " compartida, aceptada como nuevo mínimo de la dimension: " << dimension;
                            file_commonLog.writeln(printStream, flagVerbose);
                        }
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
                printStream <<"} Mínimos globales:[";
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


double Heuristic_DifferentialEvolution::generarNumeroAleatorio(double minimo, double maximo) {
    double numeroAleatorio = minimo + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (maximo - minimo)));
    return numeroAleatorio;
}


void Heuristic_DifferentialEvolution::checkAndSendMinimun(double posTemp, float oldMin, float newMin, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){

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


bool Heuristic_DifferentialEvolution::checkAndReciveMinimun(float *data,  FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
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