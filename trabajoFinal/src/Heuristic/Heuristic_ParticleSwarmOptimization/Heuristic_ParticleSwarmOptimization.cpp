#include "Heuristic_ParticleSwarmOptimization.h"


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

bool Heuristic_ParticleSwarmOptimization::execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);
    

/* 
    Scanner sc = new Scanner(System.in);
    int dimensions = Integer.parseInt(args[0]);
    int iterations = Integer.parseInt(args[1]);
    int poblation = Integer.parseInt(args[2]);
    float inertiaFactor = Float.parseFloat(args[3]);
    float personalFactor = Float.parseFloat(args[4]);
    float grupalFactor = Float.parseFloat(args[5]);

    World world = new World(dimensions, poblation, DIMENSION_MIN_VALUE, DIMENSION_MAX_VALUE, MAX_VELOCITY_ABSOLUTE_VALOR);
    if (VERBOSE_FLAG) {
        System.out.println("\nInitial World..:");
        world.print_all();
        System.out.println("\n\n");
    }

    Double newVelocity = 0.0d;
    Double newPosition = 0.0d;
    Double resultFitness_actualposition = 0.0d;
    Double resultFitness_bestPositionPersonal = 0.0d;
    Double resultFitness_bestPositionGlobal = 0.0d;
    Double posTemp = 0.0d;
    int lastIteration = 0;
    boolean flagEnd = false;

    ArrayList<Double> minPointList = new ArrayList<Double>();
    for(int i=0 ; i<dimensions ; i++){
        minPointList.add(  ((Math.random() * (DIMENSION_MAX_VALUE - DIMENSION_MIN_VALUE)) + DIMENSION_MIN_VALUE) );
    }

    for (int iteration = lastIteration; iteration < iterations; iteration++) {

        // Paso 1: Actualización del vector de velocidades por cada partícula
        for (int particle = 0; particle < world.getInfo_particleList_size(); particle++) {
            for (int dimension = 0; dimension < world.getInfo_dimensionList_size(); dimension++) {

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
                
                //System.out.println("Velocidad calculada: " + newVelocity + "\n");
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
    
    System.out.println("\n\nFINALIZACIÓN..:"); */

    
    return true;
}

