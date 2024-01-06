#include <cstdlib>
#include <ctime>
#include "Heuristic_ParticleSwarmOptimization.h"

static final boolean VERBOSE_FLAG = true;
static final int ITERATIONS_CHECK = 1; // Valor mayor que 0
static final Double DIMENSION_MIN_VALUE = - 100d;
static final Double DIMENSION_MAX_VALUE = 100d;
static final Double MAX_VELOCITY_ABSOLUTE_VALOR = DIMENSION_MAX_VALUE/10;

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

bool Heuristic_ParticleSwarmOptimization::execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
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

    double newVelocity = 0.0;
    double newPosition = 0.0;
    double resultFitness_actualposition = 0.0;
    double resultFitness_bestPositionPersonal = 0.0;
    double resultFitness_bestPositionGlobal = 0.0;
    double posTemp = 0.0;
    int lastIteration = 0;
    bool flagEnd = false;


    
    vector<double> minPointList = vector<double>();
    for(int i=0 ; i<dimensions ; i++){
        minPointList.push_back(  worldConfiguration.getLimitLeft() + static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX / (worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft()))) );
    }
    vector<vector<float>> velocityList = vector<vector<float>>();
    for(int i=0 ; i<poblation ; i++){
        for(int j=0 ; j<dimensions; j++)
        vector[i][j].push_back(0.0);
    }




    for (int iteration = lastIteration; iteration < iterations; iteration++) {

        // Paso 1: Actualización del vector de velocidades por cada partícula
        for (int particle = 0; particle < poblation; particle++) {
            for (int dimension = 0; dimension < dimensions; dimension++) {

                //System.out.println("Velocidad actual: " + world.getElement_particleList_byIndex(particle).getElement_actualVelocityList_byIndex(dimension));

                newVelocity = inertiaFactor * world.getElement_particleList_byIndex(particle).getElement_actualVelocityList_byIndex(dimension);
                newVelocity = newVelocity + (personalFactor * random0to1() *
                        (world.getElement_particleList_byIndex(particle).getElement_bestPositionList_personal_byIndex(dimension)
                        - world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension)));
                newVelocity = newVelocity + (grupalFactor * random0to1() *
                        (minPointList.get(dimension)
                        - world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension)));

                if(newVelocity > Math.abs(MAX_VELOCITY_ABSOLUTE_VALOR)){
                    newVelocity = MAX_VELOCITY_ABSOLUTE_VALOR;
                }else if(newVelocity < (- Math.abs(MAX_VELOCITY_ABSOLUTE_VALOR))){
                    newVelocity = - Math.abs(MAX_VELOCITY_ABSOLUTE_VALOR);
                }
                world.getElement_particleList_byIndex(particle).modifyElement_actualVelocityList_byIndex(dimension, newVelocity);                
            }
        }

        // Paso 2: Actualización del vector de posición por cada partícula
        for (int particle = 0; particle < world.getInfo_particleList_size(); particle++) {
            for (int dimension = 0; dimension < world.getInfo_dimensionList_size(); dimension++) {

                newPosition = world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension);
                //System.out.println("posicion actual: " +newPosition);

                newPosition = newPosition + world.getElement_particleList_byIndex(particle).getElement_actualVelocityList_byIndex(dimension);
                
                if (newPosition < world.getElement_dimensionList_byIndex(dimension).getMinValue()) {
                    newPosition = world.getElement_dimensionList_byIndex(dimension).getMinValue();
                } else if (newPosition > world.getElement_dimensionList_byIndex(dimension).getMaxValue()) {
                    newPosition = world.getElement_dimensionList_byIndex(dimension).getMaxValue();
                }
                world.getElement_particleList_byIndex(particle).modifyElement_actualPositionList_byIndex(dimension, newPosition);
                //System.out.println("Posicion calculada: " +newPosition+"\n");
            }
        }

        // Paso 3: Actualización de los minimos locales y globales
        for (int particle = 0; particle < world.getInfo_particleList_size(); particle++) {
            for (int dimension = 0; dimension < world.getInfo_dimensionList_size(); dimension++) {

                posTemp = world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension);

                resultFitness_actualposition = fitnessFunction(posTemp);
                resultFitness_bestPositionPersonal = fitnessFunction(world.getElement_particleList_byIndex(particle).getElement_bestPositionList_personal_byIndex(dimension));
                resultFitness_bestPositionGlobal = fitnessFunction(minPointList.get(dimension));

                if (resultFitness_actualposition < resultFitness_bestPositionPersonal) {
                    world.getElement_particleList_byIndex(particle).modifyElement_bestPositionList_personal_byIndex(dimension, posTemp);
                }
                if (resultFitness_actualposition < resultFitness_bestPositionGlobal) {
                    minPointList.set(dimension, posTemp);
                }
            }
        }


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
        System.out.println("\n\n");
    }
    
    System.out.println("\n\nFINALIZACIÓN..:");

    
    return true;
}


double random0to1() {
    srand(std::time(0));
    double numeroAleatorio = rand() / (double)RAND_MAX;
    return numeroAleatorio;
}