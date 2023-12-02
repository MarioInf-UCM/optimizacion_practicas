package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;

import src.graph.Graph;
import src.graph.edge.Edge;

public class Main{

    private static String filePath = "";

    public static void main(String[] args) throws FileNotFoundException, IOException{
   
        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }

        Main.filePath = args[0];
        Graph graph = Graph.ensambleGraph_byFile(Main.filePath);
        int numNodesResult = 0;
        
        MatchingMaximal(graph);
        for(int i=0 ; i<graph.getNodeList().size() ; i++){
            if(graph.getNodeList().get(i).getValue() == 1){
                numNodesResult ++;
            }
        }
        System.out.println("Numero de nodos totales: "+graph.getNodeList().size());
        System.out.println("Numero de nodos elegidos: "+numNodesResult);
        graph.printGraphSimple();
        
    }
    
    
    public static void MatchingMaximal(Graph graph){
        Graph graphOperation = new Graph(graph);
        Random random = new Random();
        Edge edgeTemp;
        int numEdgesTemp = graphOperation.countEdges();
        int randomEdge=0;

        while(numEdgesTemp>0){

            if(numEdgesTemp>1){
                randomEdge = random.ints(1, numEdgesTemp).findFirst().getAsInt();
            }
            
            edgeTemp = graphOperation.selectEdge_byPosition(randomEdge);

            graphOperation.getNodeList().get(edgeTemp.getIdSource()-1).modifyEdgeList_deleteAllNodes();
            graph.getNodeList().get(edgeTemp.getIdSource()-1).setValue(1);
            
            graphOperation.getNodeList().get(edgeTemp.getIdDestine()-1).modifyEdgeList_deleteAllNodes();
            graph.getNodeList().get(edgeTemp.getIdDestine()-1).setValue(1);

            numEdgesTemp = graphOperation.countEdges();
        }
    }
    

    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 1) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\"");
            System.out.println("\tgrafoURL: Dirección del archivo que contiene la definición del grafo.");
            return false;
        }
        System.out.println("Ejecución algoritmo `Matching Maximal'. Parámetros:");
        System.out.println("\tDirección del grafo: " + args[0]);
        return true;
    }


}