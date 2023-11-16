package world.dimension;

public class Dimension {

    private String description = "No description";
    private double minValue = Double.MIN_VALUE;
    private double maxValue = Double.MAX_VALUE;

    public Dimension(){
    }
    public Dimension(Dimension dimension){
        this.setDescription(dimension.getDescription());
        this.setMinValue(dimension.getMinValue());
        this.setMaxValue(dimension.getMaxValue());
    }
    public Dimension(double nMinValue, double nMaxValue){
        this.setMinValue(nMinValue);
        this.setMaxValue(nMaxValue);
    }
    public Dimension(String nDescription, double nMinValue, double nMaxValue){
        this.setDescription(nDescription);
        this.setMinValue(nMinValue);
        this.setMaxValue(nMaxValue);
    }



    public void print(){
        System.out.print(this.getDescription() + "    Range: " + this.getMinValue() + " to " + this.getMaxValue());
    }


    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public String getDescription(){ return this.description; }
    public void setDescription(String data){ this.description = data; }


    public double getMinValue(){ return this.minValue; }
    public void setMinValue(double data){ this.minValue = data; }
    

    public double getMaxValue(){ return this.maxValue; }
    public void setMaxValue(double data){ this.maxValue = data; }




}



