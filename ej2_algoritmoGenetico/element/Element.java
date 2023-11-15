package element;

import java.util.ArrayList;

public class Element{


    private ArrayList<Boolean> valueList = new ArrayList<Boolean>();
    private int fitnessValue = -1;


    public Element(){
    }
    public Element(ArrayList<Boolean> nValueList){
        setValueList_duplicate(nValueList);
        setFitnessValue(-1);
    }
    public Element(int sizeValueList , Boolean random){
        this.valueList = new ArrayList<Boolean>();
        for(int i=0 ; i<sizeValueList ; i++){
            this.valueList.add(getRandomBoolean());
        }
        setFitnessValue(-1);
    }


    /*******************************
     * ZONA DE DEFINICIÓN DE MÉTODOS 
     *******************************/ 

     public boolean getRandomBoolean() {
        return Math.random() < 0.5;
    }
 
    public void printElement(){
        System.out.print("\tfitnessValue: "+this.getFitnessValue()+" <");
        for(int i=0 ; i<this.valueList.size() ; i++){
            if(this.getValue_byIndex(i)){
                System.out.print("1");
            }else{
                System.out.print("0");
            }
        }
        System.out.println(">");
    }



    /*********************************************************************
     * ZONA DE DEFINICIÓN DE MÉTODOS PARA EL TRATAMIENTO DE LOS ATRIBUTOS
     *********************************************************************/
    public ArrayList<Boolean> getValueList(){return valueList;}
    public void setValueList_reference(ArrayList<Boolean> value){ this.valueList = value; }
    public void setValueList_duplicate(ArrayList<Boolean> value){
        ArrayList<Boolean> result = new ArrayList<Boolean>();
        for(int i=0 ; i<value.size() ; i++){
            result.add(value.get(i));
        }
        this.valueList = value;
        return;
    }

    public Boolean getValue_byIndex(int index){
        return this.valueList.get(index);
    }



    public int getFitnessValue(){ return this.fitnessValue;}
    public void setFitnessValue(int value){ this.fitnessValue = value;}
    

   
    




}