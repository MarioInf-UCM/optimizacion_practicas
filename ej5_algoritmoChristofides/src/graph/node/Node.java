package src.graph.node;

import java.util.ArrayList;

import src.graph.edge.Edge;

public class Node{

    private String ID = ""; 
    private int value = -1;
    private ArrayList<Edge> edgeList = new ArrayList<Edge>();


    public Node(){
    }
    public Node(Node nNode){
        this.setID(nNode.getID());
        this.setValue(nNode.getValue());
        this.setEdgeList_duplicate(nNode.getEdgeList());
    }
    public Node(String nId, int nValue, ArrayList<Edge> nEdgeList){
        this.setID(nId);
        this.setValue(nValue);
        if(nEdgeList!=null){
            this.edgeList = nEdgeList;
        }
    }


    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/

    public void addEdge(Edge n){
        this.edgeList.add(n);
    }

    public void printNodeComplet(){
        System.out.print("\t[ ID: "+this.getID()+" | Val: "+this.getValue()+ "]");
        for(int i=0 ; i<this.edgeList.size() ; i++){
            System.out.print("    ");
            this.edgeList.get(i).printEdgeComplet();
        }
        System.out.println("");
    }

    public void printNodeSimple(){
        System.out.print("\t[ "+this.getID()+ "]");
        for(int i=0 ; i<this.edgeList.size() ; i++){
            System.out.print("    ");
            this.edgeList.get(i).printEdgeSimple();
        }
        System.out.println("");
    }


    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public String getID(){ return ID; }
    public void setID(String n){ this.ID=n; }


    public int getValue(){ return this.value; }
    public void setValue(int n){ this.value=n; }


    public ArrayList<Edge> getEdgeList(){ return edgeList; }
    public Edge getEdge_byIndex(int pos){
        return getEdgeList().get(pos);
    }
    public void setEdgeList_reference(ArrayList<Edge> n){this.edgeList = new ArrayList<Edge>(n);}
    public void setEdgeList_duplicate(ArrayList<Edge> n){ 
        this.edgeList = new ArrayList<Edge>();
        Edge edghTemp;
        for(int i=0 ; i<n.size() ; i++){
            edghTemp = new Edge(n.get(i));
            this.edgeList.add(edghTemp);
        }
    }
    public void modifyEdgeList_addEdge(Edge n){
        Edge nEdge = new Edge(n);
        this.edgeList.add(nEdge);
    }
    public void modifyEdgeList_deleteAllNodes(){
        this.getEdgeList().clear();
    }


}

