package src.graph;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

import src.graph.edge.Edge;
import src.graph.node.Node;

import java.io.FileNotFoundException;
import java.io.IOException;

public class Graph{

    private String ID = "";
    private ArrayList<Node> nodeList = new ArrayList<Node>();

    public Graph(){
    }
    public Graph(Graph nGraph){
        this.setID(nGraph.getID());
        this.setNodeList_duplicate(nGraph.getNodeList());
    }
    public Graph(String nId, ArrayList<Node> nNodeList){
        this.setID(nId);
        this.nodeList = nNodeList;
    }


    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/
    
    public void printGraphComplet(){
        System.out.println("{");
        System.out.println("ID: "+this.getID());
        for( int i =0 ; i<nodeList.size() ; i++){
            this.nodeList.get(i).printNodeComplet();
        }
        System.out.println("}\n");
    }


    public void printGraphSimple(){
        System.out.println("{");
        System.out.println("ID: "+this.getID());
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


    public Graph ensamblePonderateGraph_byFileTXT(String filePath) throws FileNotFoundException, IOException{

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
                        nodeTemp = new Node( String.valueOf(i), -1, new ArrayList<Edge>() );
                        graphResult.modifyNodeList_addNode(nodeTemp);
                    }
                    firstLineFlag = false;

                }else{
                    parts = line.split(" ", 3);
                    edgeTemp = new Edge(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]));
                    edgeTemp.setDistance(Float.parseFloat(parts[2]));
                    graphResult.getNodeList().get(Integer.parseInt(parts[0])-1).addEdge(edgeTemp);
                
                }
            }
        } catch (IOException e) {
            System.out.println("TryCatch Error..:");
            e.printStackTrace();
        }

        return graphResult;
    }



    public static Graph ensamblePonderateGraph_byFileXML(String filePath) throws FileNotFoundException, IOException{

        Graph graphResult = new Graph();
        String subLine = "";
        Node nodeTemp = null;
        Edge edgeTemp = null;
        int numNode = 0;

        try(BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            for(String line; (line = br.readLine()) != null; ) {
                
                if(line.indexOf("<name>")!=-1){
                    subLine = line.replaceAll("\\s", "").split("<name>", 2)[1];
                    subLine = subLine.replaceAll("\\s", "").split("</name>", 2)[0];
                    graphResult.setID(subLine);

                }else if(line.indexOf("<vertex>")!=-1){
                    nodeTemp = new Node();
                    nodeTemp.setID(String.valueOf(numNode));
                    numNode++;
                    
                }else if(line.indexOf("</vertex>")!=-1){
                    graphResult.nodeList.add(nodeTemp);
                
                }else if(line.indexOf("<edge")!=-1){
                    edgeTemp = new Edge();
                    edgeTemp.setIdSource(numNode-1);
                    subLine = line.replaceAll("\\s", "").split("<edgecost=\"", 2)[1];
                    subLine = subLine.replaceAll("\\s", "").split("\">", 2)[0];
                    edgeTemp.setDistance(Float.parseFloat(subLine));

                    subLine = line.replaceAll("\\s", "").split("</edge>", 2)[0];
                    subLine = subLine.replaceAll("\\s", "").split("\">", 2)[1];
                    edgeTemp.setIdDestine(Integer.parseInt(subLine));
                    nodeTemp.modifyEdgeList_addEdge(edgeTemp);

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
    public String getID(){ return this.ID;}
    public void setID(String n){ this.ID = n;}

    public ArrayList<Node> getNodeList(){ return this.nodeList;}
    public Node getNode_byIndex(int pos){
        return getNodeList().get(pos);
    }
    public void setNodeList_reference(ArrayList<Node> n){this.nodeList = new ArrayList<Node>(n);}
    public void setNodeList_duplicate(ArrayList<Node> n){
        this.nodeList = new ArrayList<Node>();
        Node nodeTemp;
        for(int i=0 ; i<n.size() ; i++){
            nodeTemp = new Node(n.get(i));
            this.nodeList.add(nodeTemp);
        }
    }
    public void modifyNodeList_addNode(Node n){
        Node node = new Node(n);
        this.nodeList.add(node);
    }
    public void modifyNodeList_deleteAllNodes(){
        this.getNodeList().clear();
    }

}



