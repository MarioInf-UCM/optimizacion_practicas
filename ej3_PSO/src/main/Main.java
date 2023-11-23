package main;

import java.util.ArrayList;
import java.util.Scanner;

import world.World;



public class Main {

    public static final boolean VERBOSE_FLAG = true;
    public static final int ITERATIONS_CHECK = 1; // Valor mayor que 0
    public static final Double DIMENSION_MIN_VALUE = - 100d;
    public static final Double DIMENSION_MAX_VALUE = 100d;
    public static final Double MAX_VELOCITY_ABSOLUTE_VALOR = DIMENSION_MAX_VALUE/10;

    public static final String FITNESS_FUCTION_SELECTED = "CIRCLE";

    public static void main(String[] args) {

        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }

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

        do {
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
            
            System.out.println("\n\nFINALIZACIÓN..:");
            System.out.println("\nIteracion: " + iterations);
            System.out.print("Minimos globales:");
            for(int i=0 ; i<minPointList.size() ; i++){
                System.out.print((i+1) + minPointList.get(i) + "    ");
            }
            System.out.println("Quiere realizar más interacciones? (S/n)..: ");
            if (sc.nextLine().toUpperCase().equals("S")) {
                while (true) {
                    try {
                        System.out.println("Introduzca el número de nuevas iteraciones a realizar..: ");
                        iterations = iterations + sc.nextInt();
                        break;
                    } catch (Exception e) {
                        System.out.println("ERROR..: " + e.getMessage());
                    }
                }
            } else {
                System.out.println("Finalizando programa.");
                flagEnd = true;
            }
        } while (flagEnd == false);

        sc.close();
        return;
    }

    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 6) {
            System.out.println(
                    "Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println(
                    "java main \"Dimensión\" \"Iteraciones\" \"Poblacion\" \"FactorInercia\" \"FactorPersonal\" \"FactorGrupal\"");
            System.out.println("\tDimensión: Número de dimensiones del espacio a operar.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar.");
            System.out.println("\tPoblacion: Número de partículas con las que se va a operar.");
            System.out.println("\tFactorInercia: Peso dado a la posición anterior de la partícula a operar.");
            System.out.println("\tFactorPersonal: Peso dado a la mejor posición encontrada por al partícula a tratar.");
            System.out
                    .println("\tFactorGrupal: Peso dado a la mejor posición encontrada por el conjunto de partículas.");
            return false;
        }
        System.out.println("Ejecución algoritmo PSO Parámetros:");
        System.out.println("\tNúmero de dimensiones: " + args[0]);
        System.out.println("\tNúmero de iteraciones: " + args[1]);
        System.out.println("\tNúmero de partículas: " + args[2]);
        System.out.println("\tFactor de inercia: " + args[3]);
        System.out.println("\tFactor personal: " + args[4]);
        System.out.println("\tFactor grupal: " + args[5]);
        return true;
    }

    private static Double fitnessFunction(Double x) {
        if(FITNESS_FUCTION_SELECTED.toUpperCase().equals("CIRCLE")){
            return fitnessFunction_circle(x);
        }
        return Math.pow(x, 2);
    }

    private static Double fitnessFunction_circle(Double x) {
        return Math.pow(x, 2);
    }

    private static double random0to1() {
        return (Math.random() * 1);
    }

}