package main;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;

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

        Random rand = new Random();
        Scanner sc = new Scanner(System.in);
        int dimensions = Integer.parseInt(args[0]);
        int iterations = Integer.parseInt(args[1]);
        int poblation = Integer.parseInt(args[2]);
        float crossover = Float.parseFloat(args[3]);
        float differentialWeight = Float.parseFloat(args[4]);

        World world = new World(dimensions, poblation, DIMENSION_MIN_VALUE, DIMENSION_MAX_VALUE, MAX_VELOCITY_ABSOLUTE_VALOR);
        if (VERBOSE_FLAG) {
            System.out.println("\nInitial World..:");
            world.print_all();
            System.out.println("\n\n");
        }


        int lastIteration = 0;
        boolean flagEnd = false;
        int partSelected_1=0, indexSelected_1=0;
        int partSelected_2=0, indexSelected_2=0;
        int partSelected_3=0, indexSelected_3=0;
        int dimensionSelected=0;
        Double newPosition = 0.0d;

        ArrayList<Integer>particleSelectorList = new ArrayList<Integer>();
        for(int i=0 ; i<poblation ; i++){
            particleSelectorList.add(i);
        }

        ArrayList<Double> minPointList = new ArrayList<Double>();
        for(int i=0 ; i<dimensions ; i++){
            minPointList.add(  ((Math.random() * (DIMENSION_MAX_VALUE - DIMENSION_MIN_VALUE)) + DIMENSION_MIN_VALUE) );
        }

        do {
            for (int iteration = lastIteration; iteration < iterations; iteration++) {
                for (int particle = 0; particle < world.getInfo_particleList_size(); particle++) {
                    
                    // Paso 1: Seleccionamos las partículas y la dimension a operar
                    indexSelected_1 = rand.nextInt(particleSelectorList.size());
                    partSelected_1 = particleSelectorList.get(indexSelected_1);
                    particleSelectorList.remove(indexSelected_1);

                    indexSelected_2 = rand.nextInt(particleSelectorList.size());
                    partSelected_2 = particleSelectorList.get(indexSelected_2);
                    particleSelectorList.remove(indexSelected_2);

                    indexSelected_3 = rand.nextInt(particleSelectorList.size());
                    partSelected_3 = particleSelectorList.get(indexSelected_3);
                    particleSelectorList.remove(indexSelected_3);

                    particleSelectorList = new ArrayList<Integer>();
                    for(int i=0 ; i<poblation ; i++){
                        particleSelectorList.add(i);
                    }

                    dimensionSelected = rand.nextInt(dimensions);


                    // Paso 2: Modificamos la dimensión seleccionada
                    newPosition = modicateDimension(world, differentialWeight, dimensionSelected, partSelected_1, partSelected_2, partSelected_3);
                    if(fitnessFunction(newPosition)<fitnessFunction(world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimensionSelected))){
                        world.getElement_particleList_byIndex(particle).modifyElement_actualPositionList_byIndex(dimensionSelected, newPosition);
                        
                        if(fitnessFunction(newPosition)<fitnessFunction(minPointList.get(dimensionSelected))){
                            minPointList.set(dimensionSelected, newPosition);
                        }
                    }

                    //Paso 3: Modificamos las dimensiones restantes
                    for (int dimension = 0; dimension < world.getInfo_dimensionList_size(); dimension++) {
                        if(dimension != dimensionSelected && random0to1()<crossover){
                            newPosition = modicateDimension(world, differentialWeight, dimensionSelected, partSelected_1, partSelected_2, partSelected_3);
                            if(fitnessFunction(newPosition)<fitnessFunction(world.getElement_particleList_byIndex(particle).getElement_actualPositionList_byIndex(dimension))){
                                world.getElement_particleList_byIndex(particle).modifyElement_actualPositionList_byIndex(dimension, newPosition);
                            }
                            if(fitnessFunction(newPosition)<fitnessFunction(minPointList.get(dimension))){
                                minPointList.set(dimension, newPosition);
                            }

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
                System.out.print((i+1)+")" + minPointList.get(i) + "    ");
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

        if (args.length != 5) {
            System.out.println(
                    "Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println(
                    "java main \"Dimensión\" \"Iteraciones\" \"Poblacion\" \"Crossover\" \"DifferentialWeight\"");
            System.out.println("\tDimensión: Número de dimensiones del espacio a operar.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar.");
            System.out.println("\tPoblacion: Número de partículas con las que se va a operar.");
            System.out.println("\tCrossover: Porcentaje de dimensiones a modificar en cada iteración [0,1]");
            System.out.println("\tDifferentialWeight: Peso dado a las partículas secundarias con las que se realiza la modiciación del movimiento.");
            System.out
                    .println("\tFactorGrupal: Peso dado a la mejor posición encontrada por el conjunto de partículas.");
            return false;
        }
        System.out.println("Ejecución algoritmo PSO Parámetros:");
        System.out.println("\tNúmero de dimensiones: " + args[0]);
        System.out.println("\tNúmero de iteraciones: " + args[1]);
        System.out.println("\tNúmero de partículas: " + args[2]);
        System.out.println("\tCrossover: " + args[3]);
        System.out.println("\tPeso diferencial: " + args[4]);
        return true;
    }

    private static Double modicateDimension(World world, float differentialWeight, int dimensionSelected, int partSelected_1, int partSelected_2, int partSelected_3){
        return world.getElement_particleList_byIndex(partSelected_1).getElement_actualPositionList_byIndex(dimensionSelected) + differentialWeight * (
                            world.getElement_particleList_byIndex(partSelected_2).getElement_actualPositionList_byIndex(dimensionSelected)
                            - world.getElement_particleList_byIndex(partSelected_3).getElement_actualPositionList_byIndex(dimensionSelected));
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