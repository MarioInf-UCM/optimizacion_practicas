package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;

import src.graph.Graph;
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
        Main.iterations = Integer.parseInt(args[1]);
        ArrayList<KruskalEdge> KruskalEdgesList = null;
        Graph graph = Graph.ensamblePonderateGraph_byFileXML(graphFileURL);
        if(VERBOSE_MODE){
            System.out.println("Grafo inicial..:");
            graph.printGraphComplet();
        }


        //PASO 1: Calculamos el árbol recubridor mínimo mediante el algoritmo de Kruskal
        KruskalEdgesList = KruskalAlgorithm.kruskalMST(graphTo_KruskalEdgesList(graph), graph.getNodeList().size());
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
        KruskalEdgesList = findEulerianCycle(KruskalEdgesList, graph.getNodeList().size());
        if(VERBOSE_MODE){
            System.out.println("\nPASO 3: Buscamos un ciclo aureliano mediante el algoritmo de Hierholzer");
            printKruskalEdgeList(KruskalEdgesList);
        }

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


    private static ArrayList<KruskalEdge> graphTo_KruskalEdgesList(Graph graph){
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
            edgeTemp = new KruskalEdge(list.get(i).getSrc(), list.get(i).getDest(), list.get(i).getWeight());
            list.add(edgeTemp);
        }
        return list;
     }



    private static void printKruskalEdgeList(ArrayList<KruskalEdge> list){
        for(int i=0 ; i<list.size() ; i++){
            list.get(i).printComplete();
        }
        return;
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
                    edgeTemp = new KruskalEdge(oddEdgesLIst.get(i),oddEdgesLIst.get(i)+1, 1);
                }else{
                    edgeTemp = new KruskalEdge(oddEdgesLIst.get(i),0, 1);
                }
                list.add(edgeTemp);           
            }
        }
        return list;
    }


    public static ArrayList<KruskalEdge> findEulerianCycle(ArrayList<KruskalEdge> edges, int numVertices) {
        ArrayList<ArrayList<KruskalEdge>> graph = buildGraph(edges, numVertices);
        ArrayList<KruskalEdge> eulerianCycle = new ArrayList<>();
        Stack<KruskalEdge> stack = new Stack<>();
        KruskalEdge startEdge = edges.get(0);

        stack.push(startEdge);

        while (!stack.isEmpty()) {
            KruskalEdge currentEdge = stack.peek();
            int currentVertex = currentEdge.getDest();

            if (graph.get(currentVertex).size() > 0) {
                KruskalEdge nextEdge = graph.get(currentVertex).remove(0);
                stack.push(nextEdge);
            } else {
                eulerianCycle.add(0, stack.pop());
            }
        }

        return eulerianCycle;
    }

    private static ArrayList<ArrayList<KruskalEdge>> buildGraph(ArrayList<KruskalEdge> edges, int numVertices) {
        ArrayList<ArrayList<KruskalEdge>> graph = new ArrayList<>();

        for (int i = 0; i < numVertices; i++) {
            graph.add(new ArrayList<>());
        }

        for (KruskalEdge edge : edges) {
            graph.get(edge.getSrc()).add(edge);
            graph.get(edge.getDest()).add(edge);
        }

        return graph;
    }

}