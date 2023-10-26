package world.particle;

import java.util.ArrayList;

public class Particle {
    
    private ArrayList<Integer> actualPositionList = new ArrayList<Integer>();
    private ArrayList<Integer> bestPositionList_personal = new ArrayList<Integer>();
    private ArrayList<Integer> bestPositionList_global = new ArrayList<Integer>();
    
    public Particle(){
    }
    public Particle(Particle particle){
        this.set_actualPositionList_duplicate(particle.get_actualPositionList());
        this.set_bestPositionList_global_duplicate(particle.get_bestPositionList_personal());
        this.set_bestPositionList_global_duplicate(particle.get_bestPositionList_gloabl());
    }
    public Particle(int dimensions, boolean random){
        this.actualPositionList = new ArrayList<Integer>();
        this.bestPositionList_personal = new ArrayList<Integer>();
        this.bestPositionList_global = new ArrayList<Integer>();
        if(random){
            for(int i=0 ; i<dimensions ; i++){
                //this.actualPositionList.add( (int)(Math.random() * (maxValue + 1)));
            }
        }


    }




    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public ArrayList<Integer> get_actualPositionList(){ return this.actualPositionList; }
    public void set_actualPositionList_reference(ArrayList<Integer> data){ this.actualPositionList = data; }
    public void set_actualPositionList_duplicate(ArrayList<Integer> data){ 
        this.actualPositionList = new ArrayList<Integer>();
        for(int i=0 ; i<data.size() ; i++){
            this.actualPositionList.add(data.get(i));
        }
        return;
    }
    public Integer getElement_actualPositionList_byIndex(int index){ return this.actualPositionList.get(index); }
    

    
    public ArrayList<Integer> get_bestPositionList_personal(){ return this.bestPositionList_personal; }
    public void set_bestPositionList_personal_reference(ArrayList<Integer> data){ this.bestPositionList_personal = data; }
    public void set_bestPositionList_personal_duplicate(ArrayList<Integer> data){ 
        this.bestPositionList_personal = new ArrayList<Integer>();
        for(int i=0 ; i<data.size() ; i++){
            this.bestPositionList_personal.add(data.get(i));
        }
        return;
    }
    public Integer getElement_actualPositionList_personal_byIndex(int index){ return this.bestPositionList_personal.get(index); }
    


    public ArrayList<Integer> get_bestPositionList_gloabl(){ return this.bestPositionList_global; }
    public void set_bestPositionList_global_reference(ArrayList<Integer> data){ this.bestPositionList_global = data; }
    public void set_bestPositionList_global_duplicate(ArrayList<Integer> data){ 
        this.bestPositionList_global = new ArrayList<Integer>();
        for(int i=0 ; i<data.size() ; i++){
            this.bestPositionList_global.add(data.get(i));
        }
        return;
    }
    public Integer getElement_actualPositionList_global_byIndex(int index){ return this.bestPositionList_global.get(index); }

    










}
