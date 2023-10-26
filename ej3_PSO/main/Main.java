package main;

public class Main{

    public static void main(String[] args){

        if(!checkInitialValues(args)){
            System.out.println("\nFinalizando ejecución.");
            return;
        }

        int dimensions = Integer.parseInt(args[0]);
        int iterations = Integer.parseInt(args[1]);
        int poblation = Integer.parseInt(args[2]);
        int inertiaFactor = Integer.parseInt(args[3]);
        int personalFactor = Integer.parseInt(args[4]);
        int grupalFactor = Integer.parseInt(args[5]);

        














    }
    


    private static Boolean checkInitialValues(String[] args){

        if(args.length!= 6){
            System.out.println("Número de parámetros de entrada inválidos("+ args.length+"). La ejecución debser del tipo:");
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
        System.out.println("\tNúmero de dimensiones:"+args[0]);
        System.out.println("\tNúmero de iteraciones:"+args[1]+"\n");
        System.out.println("\tNúmero de partículas:"+args[2]+"\n");
        System.out.println("\tFactor de inercia:"+args[3]+"\n");
        System.out.println("\tFactor personal:"+args[4]+"\n");
        System.out.println("\tFactor grupal:"+args[5]+"\n");
        return true;
    }


    


}