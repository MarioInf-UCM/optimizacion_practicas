package main;

import world.World;

public class Main{

    public static void main(String[] args){

        if(!checkInitialValues(args)){
            System.out.println("\nFinalizando ejecución.");
            return;
        }

        int dimensions = Integer.parseInt(args[0]);
        int iterations = Integer.parseInt(args[1]);
        int poblation = Integer.parseInt(args[2]);
        float inertiaFactor = Float.parseFloat(args[3]);
        float personalFactor = Float.parseFloat(args[4]);
        float grupalFactor = Float.parseFloat(args[5]);

        World world = new World(dimensions, poblation, true);
        System.out.println("\nInitial World..:");
        world.print_all();
        System.out.println();

        Double newVelocity = 0.0d;
        double newPosition = 0.0d;

        for(int iteration=0 ; iteration<iterations ; iteration++){
            
            //Paso 1: Actualización del vector de velocidades por cada partícula
            for(int particle=0 ; particle<world.getInfo_particleList_size() ; particle++){
                for(int dimension=0 ; dimension<world.getInfo_dimensionList_size() ; dimension++){

                    newVelocity = inertiaFactor * world.getElement_particleList_byIndex(particle).getElement_actualVelocityList_byIndex(dimension);
                    newVelocity = newVelocity + ( personalFactor * random0to1() * 
                                    (world.getElement_particleList_byIndex(particle).getElement_bestPositionList_personal_byIndex(dimension) 
                                    - world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension) 
                                    ));
                    newVelocity = newVelocity + ( grupalFactor * random0to1() * 
                                    (world.getElement_particleList_byIndex(particle).getElement_bestPositionList_global_byIndex(dimension) 
                                    - world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension) 
                                    ));   
                }
            }
            //Paso 2: Actualización del vector de posición por cada partícula
            for(int particle=0 ; particle<world.getInfo_particleList_size() ; particle++){
                for(int dimension=0 ; dimension<world.getInfo_dimensionList_size() ; dimension++){

                    newPosition = world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension);
                    newPosition = newPosition + world.getElement_particleList_byIndex(particle).getElement_actualVelocityList_byIndex(dimension);
                    world.getElement_particleList_byIndex(particle).modifyElement_actualPositionList_byIndex(dimension, newPosition);
                }
            }



            //System.out.println("Iteracion: " + (iteration+1) + ", particulas:");
            //world.print_onlyParticles();
        }



    }
    


    private static Boolean checkInitialValues(String[] args){

        if(args.length!= 6){
            System.out.println("Número de parámetros de entrada inválidos("+ args.length+"). La ejecución debe ser del tipo:");
            System.out.println("java main \"Dimensión\" \"Iteraciones\" \"Poblacion\" \"FactorInercia\" \"FactorPersonal\" \"FactorGrupal\"");
            System.out.println("\tDimensión: Número de dimensiones del espacio a operar.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar.");
            System.out.println("\tPoblacion: Número de partículas con las que se va a operar.");
            System.out.println("\tFactorInercia: Peso dado a la posición anterior de la partícula a operar.");
            System.out.println("\tFactorPersonal: Peso dado a la mejor posición encontrada por al partícula a tratar.");
            System.out.println("\tFactorGrupal: Peso dado a la mejor posición encontrada por el conjunto de partículas.");
            return false;
        }
        System.out.println("Ejecución algoritmo PSO Parámetros:");
        System.out.println("\tNúmero de dimensiones: "+args[0]);
        System.out.println("\tNúmero de iteraciones: "+args[1]);
        System.out.println("\tNúmero de partículas: "+args[2]);
        System.out.println("\tFactor de inercia: "+args[3]);
        System.out.println("\tFactor personal: "+args[4]);
        System.out.println("\tFactor grupal: "+args[5]);
        return true;
    }


    private static Double fitnessFunction_circle(Double x){
        return Math.pow(x, 2);
    }

    private static double random0to1(){
        return ((Math.random() * 1) + 1 );
    }



}