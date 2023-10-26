package world;

import java.util.ArrayList;
import world.particle.Particle;


public class World {

    private long width = 0;
    private long length = 0;
    private long dimensions = 0;
    private ArrayList<Particle> particleList = new ArrayList<Particle>();

    public World(){

    }





    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public long get_width(){ return this.width; };
    public void set_width(long data){ this.width=data; };


    public long get_length(){ return this.length; };
    public void set_length(long data){ this.length=data; };

    
    public long get_dimensions(){ return this.dimensions; };
    public void set_dimensions(long data){ this.dimensions=data; };


    public ArrayList<Particle> get_particleList(){ return this.particleList; }
    public void set_particleList_reference(ArrayList<Particle> data){ this.particleList = data; }
    public void set_particleList_duplicate(ArrayList<Particle> data){ 
        Particle particleTemp;
        for(int i=0 ; i<data.size() ; i++){
            particleTemp = new Particle(data.get(i));
            this.particleList.add(particleTemp);
        }
        return;
    }
    public Particle getElement_particleList_byIndex(int index){ return this.particleList.get(index); }



}