package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

import src.graph.Graph;
import src.graph.edge.Edge;

public class Main{

    public static void main(String[] args) throws FileNotFoundException, IOException{
    
        
        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }

        Scanner sc = new Scanner(System.in);
        String graphFileURL = args[0];
        int iterations = Integer.parseInt(args[1]);
        float pheromoneControl = Float.parseFloat(args[2]);
        float desirabilityControl = Float.parseFloat(args[3]);

        Graph graph = Graph.ensamblePonderateGraph_byFile(graphFileURL);
        System.out.println("Grafo inicial..:");
        graph.printGraphSimple_withValue();


        for(int iteration=0 ; iteration<iterations ; iteration++){



            
        }


    }
    

    


    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 4) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\" \"Iteraciones\" \"ControlFeromonas\" \"ControlDeseabilidad\"");
            System.out.println("\tgrafoURL: Dirección dle archivo que contiene la definición del grafo.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar.");
            System.out.println("\tControlFeromonas: Controla la influencia de las feromonas [0,1]");
            System.out.println("\tControlDeseabilidad: Controla la deseabilidad de los caminos [0,1]");
            return false;
        }
        System.out.println("Ejecución algoritmo `Ant Colony Optimization'. Parámetros:");
        System.out.println("\tDirección del grafo: " + args[0]);
        System.out.println("\tNúmero de iteraciones: " + args[1]);
        System.out.println("\tControl de feromonas: " + args[2]);
        System.out.println("\tControl de deseabilidad: " + args[3]);
        return true;
    }




}