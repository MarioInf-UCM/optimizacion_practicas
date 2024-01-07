#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Heuristic_ParticleSwarmOptimization.h"

#define ITERATIONS_CHECK  1; // Valor mayor que 0
#define MAX_VELOCITY_PERCENTAGE = 10;

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
                }
                
            }
        }

        printStream <<"Proceso: " << rank << " - Iteración: " << iteration << " Mínimos gobales[ ";
        for(int i=0 ; i<minPosList.size() ; i++){
            printStream << minPosList[i] << " ";
        }
        printStream << "]";
        file_commonLog.writeln(printStream, flagVerbose);

/* 
        lastIteration = iteration;
        if (VERBOSE_FLAG) {
            System.out.println("\nIteracion: " + (iteration + 1));
            System.out.print("Minimos globales:");
            for(int i=0 ; i<minPointList.size() ; i++){
                System.out.print((i+1) +")"+ minPointList.get(i) + "    ");
            }
            world.print_onlyParticles();
        } else if ((ITERATIONS_CHECK > 0) && (((iteration + 1) % ITERATIONS_CHECK) == 0)) {
            System.out.println("\nIteracion: " + (iteration + 1));
            System.out.print("Minimos globales:");
            for(int i=0 ; i<minPointList.size() ; i++){
                System.out.print((i+1) + minPointList.get(i) + "    ");
            }
        }
        System.out.println("\n\n"); */
    }
    
    return true;
}


double Heuristic_ParticleSwarmOptimization::generarNumeroAleatorio(double minimo, double maximo) {
    srand(static_cast<unsigned int>(std::time(0)));
    double numeroAleatorio = minimo + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (maximo - minimo)));
    return numeroAleatorio;
}