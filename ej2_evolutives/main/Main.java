package main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

import graph.Graph;
import element.Element;

public class Main{

    public static void main(String[] args) throws FileNotFoundException, IOException{
        
        if(args.length!= 2){
            System.out.println("Número de parámetros de entrada inválidos("+ args.length+"). La ejecución debser del tipo:");
            System.out.println("java main \"poblacionInicial\" \"numeroIteraciones\"");
            return;
        }else{
            System.out.println("Ejecución algoritmo evolutivo de Vertex Cover. Parámetros:");
            System.out.println("\tPoblación inicial:"+args[0]);
            System.out.println("\tNúmero de iteraciones:"+args[1]+"\n");
        }

        final int mutationPercent = 75; //0-100

        String filePath = "/home/mario/Documentos/universidad/optimizacion/data/test.gr";        
        Graph graph = Graph.ensambleGraph_byFile(filePath);
        ArrayList<Element> elementList = new ArrayList<Element>();
        Element elementTemp;

        //PASO 1: Gerenamos la población inicial
        for(int i=0 ; i<Integer.parseInt(args[0]) ; i++){
            elementTemp = new Element(graph.getNodeList().size(), true);
            elementList.add(elementTemp);
        }

        
        for(int i=0 ; i<Integer.parseInt(args[1]); i++){

            //PASO 2: Calculamos el fitness de la población actual
            for(int j=0 ; j<elementList.size(); j++){
                elementList.get(j).setFitnessValue(fitnessFunction(elementList.get(j), graph));
            }
            
            //PASO 3: Realizamos la selección por ruleta
            elementList = rulette(elementList);
            
            //PASO 4: Generamos los nuevos elementos de la población
            mutateElements(elementList, mutationPercent);
            
        }
        printPoblation(elementList);
        
        int result=-0;
        int temMin=99999;
        int tempValue=-0;
        for(int i=0 ; i<elementList.size() ; i++){
            tempValue=0;
            for( int j=0 ; j<elementList.get(i).getValueList().size() ; j++){
                if(elementList.get(i).getValue_byIndex(j)){
                    tempValue++;
                }
            }
            if(tempValue<temMin){
                temMin = tempValue;
                result = i;
            }
        }

        System.out.println("RESULTADOS - Elemento seleccionado: " +result + "numNodos:" +temMin);




        return;
    }

    

    public static int fitnessFunction(Element element, Graph graph){
        int maxFitnessValue = graph.countEdges() + graph.getNodeList().size();
        int result = maxFitnessValue;

        if(element.getFitnessValue()!=-1){
            return element.getFitnessValue();
        }

        for(int i=0 ; i<element.getValueList().size() ; i++){
            if(element.getValue_byIndex(i)){
                result--;
            }else{
                result = result - graph.getPart_NodeList_byIndex(i).getEdgeList().size();
            }
        }

        return result;
    }

    

    public static ArrayList<Element> rulette(ArrayList<Element> poblation){
        
        ArrayList<Element> result = new ArrayList<Element>();
        int times = poblation.size()/2;
        int maxValue = -1;
        int selection = -1;
        for(int i=0 ; i<times ; i++){
            maxValue=0;
            for(int j=0 ; j<poblation.size() ; j++){
                maxValue = maxValue + poblation.get(j).getFitnessValue();
            }
            selection = (int)(Math.random() * (maxValue + 1));
            for(int j=0 ; j<poblation.size() ; j++){
                if(poblation.get(j).getFitnessValue() < selection){
                    selection = selection - poblation.get(j).getFitnessValue();
                }else{
                    result.add(poblation.get(j));
                    poblation.remove(j);
                    break;
                }
                
            }
        }

        return result;
    }



    public static void printPoblation(ArrayList<Element> poblation){
        System.out.println("[");
        for(int i=0 ; i<poblation.size() ; i++){
            poblation.get(i).printElement();
        }
        System.out.println("]");

        return;
    }



    public static void mutateElements(ArrayList<Element> poblation, int mutationPercent){

        Element tempElement = null;
        int randomValue = 0;
        int numNewElements = poblation.size();

        for(int i=0 ; i<numNewElements ; i++){
            tempElement = new Element(poblation.get(i).getValueList().size(), true);
            for(int j=0 ; j<poblation.get(i).getValueList().size() ; j++){
                randomValue = (int)(Math.random() * (100 + 1));
                if(randomValue>mutationPercent){
                    tempElement.getValueList().set(j, !poblation.get(i).getValueList().get(j) );
                }
                
            }
            poblation.add(tempElement);
        }      
    }



}