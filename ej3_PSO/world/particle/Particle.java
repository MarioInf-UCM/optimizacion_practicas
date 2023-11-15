package world.particle;

import java.util.ArrayList;
import java.util.UUID;

import world.World;

public class Particle {
    
    private String ID = "";
    private ArrayList<Double> actualPositionList = new ArrayList<Double>();
    private ArrayList<Double> actualDirectionList = new ArrayList<Double>();
    private ArrayList<Double> bestPositionList_personal = new ArrayList<Double>();
    private ArrayList<Double> bestPositionList_global = new ArrayList<Double>();
    
    public Particle(){
    }
    public Particle(Particle particle){
        this.set_ID(particle.get_ID());
        this.set_actualPositionList_duplicate(particle.get_actualPositionList());
        this.set_bestPositionList_global_duplicate(particle.get_bestPositionList_personal());
        this.set_bestPositionList_global_duplicate(particle.get_bestPositionList_gloabl());
    }
    public Particle(World world){
        this.set_ID(UUID.randomUUID().toString());
        this.actualPositionList = new ArrayList<Double>();
        this.bestPositionList_personal = new ArrayList<Double>();
        this.bestPositionList_global = new ArrayList<Double>();
        for(int i=0 ; i<world.getInfo_dimensionList_size() ; i++){
            this.actualPositionList.add(  ((Math.random() * 
                (world.getElement_dimensionList_byIndex(i).getMaxValue() - world.getElement_dimensionList_byIndex(i).getMinValue() )) + world.getElement_dimensionList_byIndex(i).getMinValue() ) );
            this.get_actualDirectionList().add(  ((Math.random() * 
                (world.getElement_dimensionList_byIndex(i).getMaxValue() - world.getElement_dimensionList_byIndex(i).getMinValue() )) + world.getElement_dimensionList_byIndex(i).getMinValue() ) );
        }
    }
    public Particle(World world, double MinLimit, double MaxLimit){
        this.set_ID(UUID.randomUUID().toString());
        this.actualPositionList = new ArrayList<Double>();
        this.bestPositionList_personal = new ArrayList<Double>();
        this.bestPositionList_global = new ArrayList<Double>();
        for(int i=0 ; i<world.getInfo_dimensionList_size() ; i++){
            this.get_actualPositionList().add(  ((Math.random() * (MaxLimit - MinLimit )) + MaxLimit ));
            this.get_actualDirectionList().add(  ((Math.random() * (MaxLimit - MinLimit )) + MaxLimit ));
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



    public ArrayList<Double> get_actualDirectionList(){ return this.actualDirectionList; }
    public void set_actualDirectionList_reference(ArrayList<Double> data){ this.actualDirectionList = data; }
    public void set_actualDirectionList_duplicate(ArrayList<Double> data){ 
        this.actualDirectionList = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.actualDirectionList.add(data.get(i));
        }
        return;
    }
    public Double getElement_actualDirectionList_byIndex(int index){ return this.actualDirectionList.get(index); }
    

    
    public ArrayList<Double> get_bestPositionList_personal(){ return this.bestPositionList_personal; }
    public void set_bestPositionList_personal_reference(ArrayList<Double> data){ this.bestPositionList_personal = data; }
    public void set_bestPositionList_personal_duplicate(ArrayList<Double> data){ 
        this.bestPositionList_personal = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.bestPositionList_personal.add(data.get(i));
        }
        return;
    }
    public Double getElement_actualPositionList_personal_byIndex(int index){ return this.bestPositionList_personal.get(index); }
    


    public ArrayList<Double> get_bestPositionList_gloabl(){ return this.bestPositionList_global; }
    public void set_bestPositionList_global_reference(ArrayList<Double> data){ this.bestPositionList_global = data; }
    public void set_bestPositionList_global_duplicate(ArrayList<Double> data){ 
        this.bestPositionList_global = new ArrayList<Double>();
        for(int i=0 ; i<data.size() ; i++){
            this.bestPositionList_global.add(data.get(i));
        }
        return;
    }
    public Double getElement_actualPositionList_global_byIndex(int index){ return this.bestPositionList_global.get(index); }

    










}
