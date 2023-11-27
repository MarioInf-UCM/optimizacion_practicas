package src.graph.edge;

import java.util.UUID;

public class Edge{

    private String ID = this.generateRandonID();
    private int idSource = -1;
    private int idDestine = -1;
    private float distance = 0;
    private float pheromone = 0;
    private float probably = 0;

    public Edge(){
    };
    public Edge(Edge nEdge){
        setID(nEdge.getID());
        setDistance(nEdge.getDistance());
        setIdSource(nEdge.getIdSource());
        setIdDestine(nEdge.getIdDestine());
    }
    public Edge(int nIdSource, int nIdDestine){
        setID(generateRandonID());
        setIdSource(nIdSource);
        setIdDestine(nIdDestine);
    }   
    public Edge(float nDistance, float nPheromone, int nIdSource, int nIdDestine){
        setID(generateRandonID());
        setDistance(nDistance);
        setPheromone(nPheromone);
        setIdSource(nIdSource);
        setIdDestine(nIdDestine);
    }


    
    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/

    public void printEdgeComplet(){
        System.out.print("<"+this.getIdSource()+"  -| Dis:"+this.getDistance()+"  Fer:" +this.getPheromone()+ "  Pro:"+this.getProbably()+ " |-  " + this.getIdDestine()+">");
    }

    public void printEdgeSimple(){
        System.out.print("<"+this.getIdSource()+"-"+this.getIdDestine()+">");
    }

    private String generateRandonID(){
        return UUID.randomUUID().toString();
    }

    /***************************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO BÁSICO DE LOS ATRIBUTOS
     ***************************************************************************/
    public String getID(){ return this.ID; }
    public void setID(String n){ this.ID=n; }
    
    public int getIdSource(){ return this.idSource; }
    public void setIdSource(int n){ this.idSource=n; }

    public int getIdDestine(){ return this.idDestine; }
    public void setIdDestine(int n){ this.idDestine=n; }

    public float getDistance(){ return this.distance; }
    public void setDistance(float n){ this.distance=n; }

    public float getPheromone(){ return this.pheromone; }
    public void setPheromone(float n){ this.pheromone=n; }

    public float getProbably(){ return this.probably; }
    public void setProbably(float n){ this.probably=n; }


}