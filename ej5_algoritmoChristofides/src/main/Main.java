package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

import src.graph.Graph;
import src.graph.edge.Edge;
import src.hierholzerAlgorithm.HierholzerAlgorithm;
import src.hierholzerAlgorithm.hierholzerEdge.HierholzerEdge;
import src.kruskalAlgorithm.KruskalAlgorithm;
import src.kruskalAlgorithm.kruskalEdge.KruskalEdge;

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
        Graph graph = Graph.ensamblePonderateGraph_byFileXML(graphFileURL);
        if(VERBOSE_MODE){
            System.out.println("Grafo inicial..:");
            graph.printGraphComplet();
        }


        //PASO 1: Calculamos el árbol recubridor mínimo mediante el algoritmo de Kruskal
        ArrayList<KruskalEdge> KruskalEdgesList = null;
        KruskalEdgesList = KruskalAlgorithm.kruskalMST(graph_To_KruskalEdgesList(graph), graph.getNodeList().size());
        if(VERBOSE_MODE){
            System.out.println("\nPASO 1: Calculamos el árbol recubridor mínimo mediante el algoritmo de Kruskal");
            printKruskalEdgeList(KruskalEdgesList);
        }

        //PASO 2: Dúplicar las aristas resultantes
        KruskalEdgesList = dupliateKruskalEdges(KruskalEdgesList);
        if(VERBOSE_MODE){
            System.out.println("\nPASO 2: Dúplicar las aristas resultantes");
            printKruskalEdgeList(KruskalEdgesList);
        }

        //PASO 3 y 4: Buscamos los nodos de grado impar y los unimos para convertirlos en nodos de grado par
        KruskalEdgesList = destroyOddEdges(KruskalEdgesList);
        if(VERBOSE_MODE){
            System.out.println("\nPASO 3 y 4: Buscamos los nodos de grado impar y los unimos para convertirlos en nodos de grado par");
            printKruskalEdgeList(KruskalEdgesList);
        }

        //PASO 5: Buscamos un ciclo aureliano mediante el algoritmo de Hierholzer
        ArrayList<HierholzerEdge> hierholzerEdgesList = new ArrayList<HierholzerEdge>();
        hierholzerEdgesList = KruskalEdgesList_To_HierholzerEdge(KruskalEdgesList);
        hierholzerEdgesList = HierholzerAlgorithm.hierholzer(hierholzerEdgesList);
        if(VERBOSE_MODE){
            System.out.println("\nPASO 5: Buscamos un ciclo aureliano mediante el algoritmo de Hierholzer");
            printHierholzerEdgeList(hierholzerEdgesList);
        }

        //PASO 6: Eliminamos los vertices repetidos
        ArrayList<Integer> nodeList = deleteRepeatedEdges(hierholzerEdgesList, graph.getNodeList().size());
        if(VERBOSE_MODE){
            System.out.println("\nPASO 6: Eliminamos los vertices repetidos");
            for(int i=0 ; i<nodeList.size() ; i++){
                System.out.print(nodeList.get(i)+"  ");
            };
        } 

        //PASO 7: Ensamblamos los resultados
        ArrayList<Edge> pathResult = new ArrayList<Edge>();
        Edge edgeTemp = null;
        int source=0, destine=0;
        for(int i=0 ; i<nodeList.size()-1 ; i++){
            source = nodeList.get(i);
            destine = nodeList.get(i+1);
            if(source>destine){
                edgeTemp = new Edge( graph.getNode_byIndex(source).getEdge_byIndex(destine));
            }else if(source<destine){
                edgeTemp = new Edge( graph.getNode_byIndex(source).getEdge_byIndex(destine-1));
            }
            pathResult.add(edgeTemp);
        }

        System.out.println("\n\nFINALIZACIÓN..:");
        for(int i=0 ; i<pathResult.size() ; i++){
            pathResult.get(i).printEdgeComplet();
            System.out.println();
        };       

        return;
    }
    


    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 1) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\" \"Iteraciones\" \"ControlFeromonas\" \"ControlDeseabilidad\" \"tEvaporacionFeromonas\"");
            System.out.println("\tgrafoURL: Dirección dle archivo que contiene la definición del grafo.");
            return false;
        }
        System.out.println("Ejecución algoritmo `Christofides'. Parámetros:");
        System.out.println("\tDirección del grafo: " + args[0]);
        return true;
    }



    private static ArrayList<KruskalEdge> graph_To_KruskalEdgesList(Graph graph){
        ArrayList<KruskalEdge> listResult = new ArrayList<KruskalEdge>();
        KruskalEdge kruskalEdgeTemp = null;

        for(int node=0 ; node<graph.getNodeList().size() ; node++){
            for(int edge=0 ; edge<graph.getNode_byIndex(node).getEdgeList().size() ; edge++){
                kruskalEdgeTemp = new KruskalEdge(graph.getNode_byIndex(node).getEdge_byIndex(edge).getIdSource(), 
                                                    graph.getNode_byIndex(node).getEdge_byIndex(edge).getIdDestine(), 
                                                    graph.getNode_byIndex(node).getEdge_byIndex(edge).getDistance());
                listResult.add(kruskalEdgeTemp);
            }
        }

        return listResult;
    }



    private static ArrayList<KruskalEdge> dupliateKruskalEdges(ArrayList<KruskalEdge> list){
        KruskalEdge edgeTemp = null;
        int initialSize = list.size();
        for(int i=0 ; i<initialSize ; i++){
            edgeTemp = new KruskalEdge(list.get(i).getDest(), list.get(i).getSrc(), list.get(i).getWeight());
            list.add(edgeTemp);
        }
        return list;
     }



    private static ArrayList<KruskalEdge> destroyOddEdges(ArrayList<KruskalEdge> list){
        
        ArrayList<Integer> oddEdgesLIst = new ArrayList<Integer>();
        KruskalEdge edgeTemp = null;
        int posTemp = 0;

        for(int i=0 ; i<list.size() ; i++){
            if(oddEdgesLIst.indexOf(list.get(i).getSrc())==-1){
                oddEdgesLIst.add(list.get(i).getSrc());
            }else{
                posTemp = oddEdgesLIst.indexOf(list.get(i).getSrc());
                oddEdgesLIst.remove(posTemp);
            }
        }
        
        if(oddEdgesLIst.size()==1){
            if(oddEdgesLIst.get(0)==0){
                edgeTemp = new KruskalEdge(oddEdgesLIst.get(0),1, 1f);
            }else{
                edgeTemp = new KruskalEdge(oddEdgesLIst.get(0),0, 1f);
            }
            list.add(edgeTemp);
        }else{
            for(int i=0 ; i<oddEdgesLIst.size() ; i++){
                if(i<oddEdgesLIst.size()-1){
                    edgeTemp = new KruskalEdge(oddEdgesLIst.get(i),oddEdgesLIst.get(i)+1, 1f);
                }else{
                    edgeTemp = new KruskalEdge(oddEdgesLIst.get(i),oddEdgesLIst.get(0), 1f);
                }
                list.add(edgeTemp);           
            }
        }
        return list;
    }


    public static ArrayList<HierholzerEdge> KruskalEdgesList_To_HierholzerEdge(ArrayList<KruskalEdge> list) {
        ArrayList<HierholzerEdge> hierholzerEdgesList = new ArrayList<HierholzerEdge>();
        HierholzerEdge hierholzerEdgeTemp;
        for (int i=0 ; i<list.size() ; i++) {
            hierholzerEdgeTemp = new HierholzerEdge(list.get(i).getSrc(), list.get(i).getDest(), list.get(i).getWeight());
            hierholzerEdgesList.add(hierholzerEdgeTemp);
        }
        return hierholzerEdgesList;
    }


    private static ArrayList<Integer> deleteRepeatedEdges(ArrayList<HierholzerEdge>list, int numNodes){
        
        
        ArrayList<Boolean> checkList = new ArrayList<Boolean>();
        for(int i=0 ; i<numNodes ; i++){
            checkList.add(false);
        }
        
        ArrayList<Integer> nodeOrderList = new ArrayList<Integer>();
        for(int i=0 ; i<list.size() ; i++){
            nodeOrderList.add(list.get(i).getSrc());
        }        
        nodeOrderList.add(list.get(list.size()-2).getDest());
        
        for(int i=0 ; i<nodeOrderList.size() ; i++){
            if(checkList.get(nodeOrderList.get(i))==false ){
                checkList.set(nodeOrderList.get(i), true);
            }else{
                nodeOrderList.remove(i);
                i--;
            }
        }

        return nodeOrderList;
    }



    private static void printKruskalEdgeList(ArrayList<KruskalEdge> list){
        for(int i=0 ; i<list.size() ; i++){
            list.get(i).printComplete();
        }
        return;
    }   

    private static void printHierholzerEdgeList(ArrayList<HierholzerEdge> list){
        for(int i=0 ; i<list.size() ; i++){
            list.get(i).printComplete();
        }
        return;
    }   



 
}
