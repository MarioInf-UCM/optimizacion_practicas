package src.kruskalAlgorithm.kruskalEdge;

public class KruskalEdge {
    private int src;
    private int dest;
    private float weight;

    public KruskalEdge(int src, int dest, float weight) {
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }



    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/
    public void printSimple() {
        System.out.print("(" + src + " - " + dest + ") ");
    }

    public void printComplete() {
        System.out.println("Edge: " + src + " - " + dest + ", Weight: " + weight);
    }


    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public int getSrc() { return src; }
    public void setSrc(int src) { this.src = src; }

    public int getDest() { return dest; }
    public void setDest(int dest) { this.dest = dest; }

    public float getWeight() { return weight; }
    public void setWeight(float weight) { this.weight = weight; }
}
