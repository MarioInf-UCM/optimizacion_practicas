package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

import src.graph.Graph;
import src.graph.edge.Edge;
import src.graph.node.Node;

public class Main{

    private static final boolean VERBOSE_MODE = true;

    private static String graphFileURL = "";
    private static int iterations = 0;
    private static float pheromoneControl = 0.0f;
    private static float desirabilityControl = 0.0f;


    public static void main(String[] args) throws FileNotFoundException, IOException{
    
        
        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }
        
        Main.graphFileURL = args[0];
        Main.iterations = Integer.parseInt(args[1]);
        Main.pheromoneControl = Float.parseFloat(args[2]);
        Main.desirabilityControl = Float.parseFloat(args[3]);

        Scanner sc = new Scanner(System.in);
        Graph graph = Graph.ensamblePonderateGraph_byFile(graphFileURL);
        Node actualNode = null;
        int actualNodePosition = 0;
        Edge selectedEdge = null;
        boolean finishAnt_Fail = false;
        boolean finishAnt_Success = false;
        int movementDoneCount = 0;

        System.out.println("Grafo inicial..:");
        graph.printGraphComplet();
        for(int iteration=0 ; iteration<iterations ; iteration++){
            
                resetGraphValue(graph);
                actualNodePosition = 0;
                movementDoneCount = 0;
                actualNode = graph.getNode_byIndex(actualNodePosition);

            
            do {    // Calculamos el recorido de una hormiga

                // Paso 1: Verificamos si existe un camino disponible
                graph.getNode_byIndex(actualNodePosition).setValue(0);
                if(!checkPosiblilities(graph, actualNode)){
                    if(checkCompleteGraph(graph)){
                        finishAnt_Success = true;
                    }else{
                        finishAnt_Fail = true;
                    }
                    break;
                }

                //Paso 2: Calculamos el proximo camino a recorrer
                calculateEdgesProbability(graph, actualNode);

                //Paso 3: Movemos a la hormiga
                selectedEdge = selectNextMovement(actualNode);
                if(VERBOSE_MODE){
                    System.out.println("\n\nNº Hormiga: "+iteration+"    nº movimiento "+movementDoneCount);
                    System.out.println("posición actual: "+actualNodePosition+ "    posoción siguiente: "+graph.getNode_byIndex(selectedEdge.getIdDestine()-1));
                    graph.printGraphComplet();
                }

                actualNode = graph.getNode_byIndex(selectedEdge.getIdDestine()-1);
                actualNodePosition = selectedEdge.getIdDestine()-1;
                finishAnt_Fail = false;
                finishAnt_Success = false;
                
                movementDoneCount++;
            } while (finishAnt_Fail || finishAnt_Success);

            if(finishAnt_Fail){
                System.out.println("La hormiga no ha encontrado el camino. La pobre ha muerto de inanición.");
            }else if(finishAnt_Success){
                System.out.println("¡¡La hormiga ha logrado encontrar el camino!!. Será recordada como un heroe.");
            }  
        }


    }
    


    private static void resetGraphValue(Graph graph){
        for(int i=0 ; i<graph.getNodeList().size() ; i++){
            graph.getNode_byIndex(i).setValue(-1);
            for(int j=0 ; j<graph.getNode_byIndex(i).getEdgeList().size() ; j++){
                graph.getNode_byIndex(i).getEdge_byIndex(j).setProbably(0);
            }
        }
        return;
    }



    private static boolean checkPosiblilities(Graph graph, Node actualNode){

        for(int i=0 ; i<actualNode.getEdgeList().size() ; i++){
            if(graph.getNode_byIndex(i).getValue() == -1){
                return true;
            }
        }
        return false;
    }



    private static boolean checkCompleteGraph(Graph graph){

        for(int i=0 ; i<graph.getNodeList().size() ; i++){
            if(graph.getNode_byIndex(i).getValue() == -1){
                return false;
            }
        }
        return true;
    }



    private static void calculateEdgesProbability(Graph graph,  Node node){
        float probablyTemp = 0.0f;
        float totalProbablyTemp = 0.0f;

        for(int i=0 ; i< node.getEdgeList().size() ; i++){

            if(graph.getNode_byIndex(node.getEdge_byIndex(i).getIdDestine()-1).getValue()!=-1){
                node.getEdge_byIndex(i).setProbably(0);              
            }else{
                probablyTemp = pheromoneControl * node.getEdge_byIndex(i).getPheromone();
                probablyTemp = probablyTemp * desirabilityControl * (1/node.getEdge_byIndex(i).getDistance());
                node.getEdge_byIndex(i).setProbably(probablyTemp);
                totalProbablyTemp = totalProbablyTemp +probablyTemp;
            }
        }

        node.setTotalProbablyEdges(totalProbablyTemp);
        for(int i=0 ; i< node.getEdgeList().size() ; i++){
            if(totalProbablyTemp==0){
                node.getEdge_byIndex(i).setProbably(0);
            }else{
                node.getEdge_byIndex(i).setProbably(node.getEdge_byIndex(i).getProbably()/totalProbablyTemp);
            }
        }

        return;
    }



    private static Edge selectNextMovement(Node node){
        int positionSelected = 0;
        float randomSelection = (float)Math.random() * node.getTotalProbablyEdges();

        for(int i=0 ; i<node.getEdgeList().size() ; i++){
            if(randomSelection <= node.getEdge_byIndex(i).getProbably()){
                positionSelected = i;
                break;
            }else{
                randomSelection = - node.getEdge_byIndex(i).getProbably();
            }
        }

        return node.getEdge_byIndex(positionSelected);
    }




    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 4) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\" \"Iteraciones\" \"ControlFeromonas\" \"ControlDeseabilidad\"");
            System.out.println("\tgrafoURL: Dirección dle archivo que contiene la definición del grafo.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar (es decir, el número de hormigas).");
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