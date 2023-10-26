package graph;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.io.IOException;

import graph.Edge;
import graph.Node;


public class Graph{

    private int id = -1;
    private ArrayList<Node> nodeList = new ArrayList<Node>();

    public Graph(){
    }
    public Graph(Graph nGraph){
        this.setId(nGraph.getId());
        this.setNodeList_duplicate(nGraph.getNodeList());
    }
    public Graph(int nId, ArrayList<Node> nNodeList){
        this.setId(nId);
        this.nodeList = nNodeList;
    }


    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/
    
    public void printGraphComplet(){
        for( int i =0 ; i<nodeList.size() ; i++){
            this.nodeList.get(i).printNodeComplet();
        }
    }


    public void printGraphSimple(){
        System.out.println("{");
        System.out.println("ID: "+this.getId());
        for( int i =0 ; i<nodeList.size() ; i++){
            this.nodeList.get(i).printNodeSimple();
        }
        System.out.println("}\n");
    }


    public int countEdges(){
        int numEdgesResult = 0;
        for(int i=0 ; i<this.getNodeList().size() ; i++){
            numEdgesResult = numEdgesResult + this.getNodeList().get(i).getEdgeList().size();
        }

        return numEdgesResult;
    }


    public Edge selectEdge_byPosition(int pos){
        Edge edgeDefault = new Edge(-20,-20);

        for(int i=0 ; i<this.getNodeList().size() ; i++){
            if(this.getNodeList().get(i).getEdgeList().size() < pos){
                pos = pos - this.getNodeList().get(i).getEdgeList().size();
            }else{
                return this.getNodeList().get(i).getEdgeList().get(pos-1);
            }
        }
        return edgeDefault;
    }


    public static Graph ensambleGraph_byFile(String filePath) throws FileNotFoundException, IOException{

        Graph graphResult = new Graph();
        Node nodeTemp;
        Edge edgeTemp;
        String[] parts = null;
        boolean firstLineFlag = true;

        try(BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            for(String line; (line = br.readLine()) != null; ) {
                
                if(firstLineFlag==true){
                    parts = line.split(" ", 4);  
                    
                    for (int i=1 ; i<=Integer.parseInt(parts[2]) ; i++){
                        nodeTemp = new Node( i, -1, new ArrayList<Edge>() );
                        graphResult.modifyNodeList_addNode(nodeTemp);
                    }
                    firstLineFlag = false;

                }else{
                    parts = line.split(" ", 2);
                    edgeTemp = new Edge(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
                    graphResult.getNodeList().get(Integer.parseInt(parts[0])-1).addEdge(edgeTemp);
                
                }
            }
        } catch (IOException e) {
            System.out.println("TryCatch Error..:");
            e.printStackTrace();
        }

        return graphResult;
    }


    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public int getId(){ return this.id;}
    public void setId(int n){ this.id = n;}

    public ArrayList<Node> getNodeList(){ return this.nodeList;}
    public void setNodeList_reference(ArrayList<Node> n){this.nodeList = new ArrayList<Node>(n);}
    public void setNodeList_duplicate(ArrayList<Node> n){ 
        this.nodeList = new ArrayList<Node>();
        Node nodeTemp;
        for(int i=0 ; i<n.size() ; i++){
            nodeTemp = new Node(n.get(i));
            this.nodeList.add(nodeTemp);
        }
    }
    public Node getPart_NodeList_byIndex(int index){ return this.nodeList.get(index);}
    public void modifyNodeList_addNode(Node n){
        Node node = new Node(n);
        this.nodeList.add(node);
    }
    public void modifyNodeList_deleteAllNodes(){
        this.getNodeList().clear();
    }

}



