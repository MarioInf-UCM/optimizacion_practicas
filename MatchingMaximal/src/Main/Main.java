package src.Main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;

import src.Graph.Graph;
import src.Graph.Edge.Edge;

public class Main{

    public static void main(String[] args) throws FileNotFoundException, IOException{
        
        String filePath = "/home/mario/Documentos/universidad/Optimizacion/MatchingMaximal/data/vc-exact_001.gr";        
        Graph graph = Graph.ensambleGraph_byFile(filePath);
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
    


}