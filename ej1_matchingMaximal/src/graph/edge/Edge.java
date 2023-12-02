package src.graph.edge;

public class Edge{

    private int id = -1; 
    private int value = -1;
    private int idSource = -1;
    private int idDestine = -1;

    public Edge(){
    };
    public Edge(Edge nEdge){
        setId(nEdge.getId());
        setValue(nEdge.getValue());
        setIdSource(nEdge.getIdSource());
        setIdDestine(nEdge.getIdDestine());
    }
    public Edge(int nId, int nValue, int nIdSource, int nIdDestine){
        setId(nId);
        setValue(nValue);
        setIdSource(nIdSource);
        setIdDestine(nIdDestine);
    }   
    public Edge(int nIdSource, int nIdDestine){
        setId(-1);
        setValue(-1);
        setIdSource(nIdSource);
        setIdDestine(nIdDestine);
    }   

    
    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/

    public void printEdgeComplet(){
        System.out.print(" <"+this.getId()+" | "+this.getValue()+" | " +this.getIdSource()+"-" + this.getIdDestine()+">");
    }

    public void printEdgeSimple(){
        System.out.print(" <"+this.getIdSource()+"-"+this.getIdDestine()+">");
    }


    /***************************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO BÁSICO DE LOS ATRIBUTOS
     ***************************************************************************/
    public int getId(){ return this.id; }
    public void setId(int n){ this.id=n; }

    public int getValue(){ return this.value; }
    public void setValue(int n){ this.value=n; }

    public int getIdSource(){ return this.idSource; }
    public void setIdSource(int n){ this.idSource=n; }

    public int getIdDestine(){ return this.idDestine; }
    public void setIdDestine(int n){ this.idDestine=n; }

}