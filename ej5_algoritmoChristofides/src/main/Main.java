package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

import src.graph.Graph;

public class Main{

    private static final boolean VERBOSE_MODE = true;
    private static final boolean FINALIZATION_CHECK = false;

    private static String graphFileURL = "";
    private static int iterations = 0;


    public static void main(String[] args) throws FileNotFoundException, IOException{
    
        
        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }
        
        Main.graphFileURL = args[0];
        Main.iterations = Integer.parseInt(args[1]);
        Graph graph = Graph.ensamblePonderateGraph_byFileXML(graphFileURL);
        if(VERBOSE_MODE){
            System.out.println("Grafo inicial..:");
            graph.printGraphComplet();
        }

        do{
  
                

            

        }while(FINALIZATION_CHECK && finalizationCheck());

        return;
    }
    


    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 2) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\" \"Iteraciones\" \"ControlFeromonas\" \"ControlDeseabilidad\" \"tEvaporacionFeromonas\"");
            System.out.println("\tgrafoURL: Dirección dle archivo que contiene la definición del grafo.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar (es decir, el número de hormigas).");
            return false;
        }
        System.out.println("Ejecución algoritmo `Christofides'. Parámetros:");
        System.out.println("\tDirección del grafo: " + args[0]);
        System.out.println("\tNúmero de iteraciones: " + args[1]);
        return true;
    }



    private static boolean finalizationCheck(){

        Scanner sc = new Scanner(System.in);
        String input;

        System.out.println("\n\nFINALIZACIÓN..:");
        System.out.println("Iteracion: " + iterations);
        System.out.println("Quiere realizar más interacciones? (S/n)..: ");
        do{
            input = sc.nextLine().toUpperCase();
            if (input.equals("S")) {
                while (true) {
                    try {
                        System.out.println("Introduzca el número de nuevas iteraciones a realizar..: ");
                        iterations = iterations + sc.nextInt();
                        break;
                    } catch (Exception e) {
                        System.out.println("ERROR..: " + e.getMessage());
                    }
                }
                break;
            } else if(input.equals("N")){
                sc.close();
                return false;
            }
        }while(true);

        sc.close();
        return true;
    }



}