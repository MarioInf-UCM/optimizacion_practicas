package src.graph.node;

import java.util.ArrayList;

import src.graph.edge.Edge;

public class Node{

    private int id = -1; 
    private int value = -1;
    private ArrayList<Edge> edgeList = new ArrayList<Edge>();


    public Node(){
    }
    public Node(Node nNode){
        this.setId(nNode.getId());
        this.setValue(nNode.getValue());
        this.setEdgeList_duplicate(nNode.getEdgeList());
    }
    public Node(int nId, int nValue, ArrayList<Edge> nEdgeList){
        this.setId(nId);
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
        System.out.print("\t[ "+this.getId()+" | "+this.getValue()+" ]");
        for(int i=0 ; i<this.edgeList.size() ; i++){
            this.edgeList.get(i).printEdgeComplet();
        }
        System.out.println("");
    }

    public void printNodeSimple(){
        System.out.print("\t[ "+this.getId()+" | "+this.getValue()+" ]");
        for(int i=0 ; i<this.edgeList.size() ; i++){
            this.edgeList.get(i).printEdgeSimple();
        }
        System.out.println("");
    }

    public void printNodeSimple_withValue(){
        System.out.print("\t[ "+this.getId()+" | "+this.getValue()+" ]");
        for(int i=0 ; i<this.edgeList.size() ; i++){
            this.edgeList.get(i).printEdgeSimple_withValue();
        }
        System.out.println("");
    }



    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public int getId(){ return id; }
    public void setId(int n){ this.id=n; }

    public int getValue(){ return value; }
    public void setValue(int n){ value=n; }

    public ArrayList<Edge> getEdgeList(){ return edgeList; }
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

