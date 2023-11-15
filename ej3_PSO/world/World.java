package world;

import java.util.ArrayList;

import world.dimension.Dimension;
import world.particle.Particle;


public class World {

    private ArrayList<Dimension> dimensionList = new ArrayList<Dimension>();
    private ArrayList<Particle> particleList = new ArrayList<Particle>();

    public World(){
    }
    public World(int dimensions, int particles){
        for(int i=0 ; i<dimensions ; i++){
            this.get_dimensionList().add(new Dimension());
            this.get_particleList().add(new Particle());
        }
    }





    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public ArrayList<Dimension> get_dimensionList(){ return this.dimensionList; }
    public void set_dimensionList_reference(ArrayList<Dimension> data){ this.dimensionList = data; }
    public void set_dimensionList_duplicate(ArrayList<Dimension> data){ 
        Dimension temp;
        for(int i=0 ; i<data.size() ; i++){
            temp = new Dimension(data.get(i));
            this.dimensionList.add(temp);
        }
        return;
    }
    public Dimension getElement_dimensionList_byIndex(int index){ return this.dimensionList.get(index); }
    public int getInfo_dimensionList_size(){ return this.get_dimensionList().size(); }



    public ArrayList<Particle> get_particleList(){ return this.particleList; }
    public void set_particleList_reference(ArrayList<Particle> data){ this.particleList = data; }
    public void set_particleList_duplicate(ArrayList<Particle> data){ 
        Particle temp;
        for(int i=0 ; i<data.size() ; i++){
            temp = new Particle(data.get(i));
            this.particleList.add(temp);
        }
        return;
    }
    public Particle getElement_particleList_byIndex(int index){ return this.particleList.get(index); }
    public int getInfo_particleList_size(){ return this.get_particleList().size(); }



}