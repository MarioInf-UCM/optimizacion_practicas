package world;

import java.util.ArrayList;

import world.dimension.Dimension;
import world.particle.Particle;


public class World {

    private ArrayList<Dimension> dimensionList = new ArrayList<Dimension>();
    private ArrayList<Particle> particleList = new ArrayList<Particle>();

    public World(){
    }
    public World(int dimensions, int particles, double dimension_minValue, double dimension_maxValue, boolean velocityZero){
        for(int i=0 ; i<dimensions ; i++){
            this.get_dimensionList().add(new Dimension(dimension_minValue, dimension_maxValue));
        }
        for(int i=0 ; i<particles ; i++){
            this.get_particleList().add(new Particle(this.get_dimensionList(), velocityZero));
        }
    }




    public void print_all(){
        System.out.println("Dimensions{");
        for(int i=0 ; i<this.getInfo_dimensionList_size() ; i++){
            this.getElement_dimensionList_byIndex(i).print();
            System.out.println();
        }
        System.out.println("}\nParticles{");
        for(int i=0 ; i<this.getInfo_particleList_size() ; i++){
            this.getElement_particleList_byIndex(i).print_all();
            System.out.println();
        }
        System.out.println("}\n");

    }

    public void print_onlyParticles(){
        System.out.println("}\nParticles{");
        for(int i=0 ; i<this.getInfo_particleList_size() ; i++){
            this.getElement_particleList_byIndex(i).print_all();
            System.out.println();
        }
        System.out.println("}\n");
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
    public void modifyElement_dimensionList_byIndex(int index, Dimension value){this.dimensionList.set(index, value);}



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
    public void modifyElement_prticleList_byIndex(int index, Particle value){this.particleList.set(index, value);}


}