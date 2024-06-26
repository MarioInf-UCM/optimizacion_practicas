package world.particle;

import java.util.ArrayList;
import java.util.UUID;

import world.dimension.Dimension;

public class Particle {
    
    private String ID = "";
    private ArrayList<Double> actualPositionList = new ArrayList<Double>();
    private ArrayList<Double> actualVelocityList = new ArrayList<Double>();
    private ArrayList<Double> bestPositionList_personal = new ArrayList<Double>();
    
    public Particle(){
    }
    public Particle(Particle particle){
        this.set_ID(particle.get_ID());
        this.set_actualPositionList_duplicate(particle.get_actualPositionList());
    }
    public Particle(ArrayList<Dimension> dimensionList, double MaxVelocity_AbsoluteValor){
        this.set_ID(UUID.randomUUID().toString());
        this.actualPositionList = new ArrayList<Double>();
        this.bestPositionList_personal = new ArrayList<Double>();
        for(int i=0 ; i<dimensionList.size() ; i++){
            this.get_actualPositionList().add(  ((Math.random() * (dimensionList.get(i).getMaxValue() - dimensionList.get(i).getMinValue() )) + dimensionList.get(i).getMinValue() ) );
            this.get_actualVelocityList().add(  ((Math.random() * (Math.abs(MaxVelocity_AbsoluteValor) + Math.abs(MaxVelocity_AbsoluteValor) )) - Math.abs(MaxVelocity_AbsoluteValor) ));
            
            this.get_bestPositionList_personal().add(this.get_actualPositionList().get(i));
        }
    }


    public void print_all(){
        System.out.print("ID: "+this.get_ID() + "\t||");
        for(int i=0 ; i<getInfo_actualPositionList_size() ; i++){
            System.out.print("\t"+(i+1)+"( X: "+getElement_actualPositionList_byIndex(i)+"\tV: " +getElement_actualVelocityList_byIndex(i)+ 
                                "\tP: "+this.getElement_bestPositionList_personal_byIndex(i) + " )" );
        }
    }


    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public String get_ID(){ return this.ID; }
    public void set_ID(String data){ this.ID = data;}



    public ArrayList<Double> get_actualPositionList(){ return this.actualPositionList; }
    public void set_actualPositionList_reference(ArrayList<Double> data){ this.actualPositionList = data; }
    public void set_actualPositionList_duplicate(ArrayList<Double> data){ 
        this.actualPositionList = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.actualPositionList.add(data.get(i));
        }
        return;
    }
    public Double getElement_actualPositionList_byIndex(int index){ return this.actualPositionList.get(index); }
    public int getInfo_actualPositionList_size(){ return this.get_actualPositionList().size(); }
    public void modifyElement_actualPositionList_byIndex(int index, Double value){this.actualPositionList.set(index, value);}



    public ArrayList<Double> get_actualVelocityList(){ return this.actualVelocityList; }
    public void set_actualVelocityList_reference(ArrayList<Double> data){ this.actualVelocityList = data; }
    public void set_actualVelocityList_duplicate(ArrayList<Double> data){ 
        this.actualVelocityList = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.actualVelocityList.add(data.get(i));
        }
        return;
    }
    public Double getElement_actualVelocityList_byIndex(int index){ return this.actualVelocityList.get(index); }
    public int getInfo_actualVelocityList_size(){ return this.get_actualVelocityList().size(); }
    public void modifyElement_actualVelocityList_byIndex(int index, Double value){this.actualVelocityList.set(index, value);}
    

    
    public ArrayList<Double> get_bestPositionList_personal(){ return this.bestPositionList_personal; }
    public void set_bestPositionList_personal_reference(ArrayList<Double> data){ this.bestPositionList_personal = data; }
    public void set_bestPositionList_personal_duplicate(ArrayList<Double> data){ 
        this.bestPositionList_personal = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.bestPositionList_personal.add(data.get(i));
        }
        return;
    }
    public Double getElement_bestPositionList_personal_byIndex(int index){ return this.bestPositionList_personal.get(index); }
    public int getInfo_bestPositionList_personal_size(){ return this.get_bestPositionList_personal().size(); }
    public void modifyElement_bestPositionList_personal_byIndex(int index, Double value){this.bestPositionList_personal.set(index, value);}



}
