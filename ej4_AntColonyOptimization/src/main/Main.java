package src.main;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;

import src.graph.Graph;
import src.graph.edge.Edge;
import src.graph.node.Node;

public class Main{

    private static final boolean VERBOSE_MODE = false;

    private static String graphFileURL = "";
    private static int iterations = 0;
    private static float pheromoneControl = 0.0f;
    private static float desirabilityControl = 0.0f;
    private static float rateEvaporationPheromone = 0.0f;


    public static void main(String[] args) throws FileNotFoundException, IOException{
    
        
        if (!checkInitialValues(args)) {
            System.out.println("\nFinalizando ejecución.");
            return;
        }
        
        Main.graphFileURL = args[0];
        Main.iterations = Integer.parseInt(args[1]);
        Main.pheromoneControl = Float.parseFloat(args[2]);
        Main.desirabilityControl = Float.parseFloat(args[3]);
        Main.rateEvaporationPheromone = Float.parseFloat(args[4]);

        Scanner sc = new Scanner(System.in);
        Graph graph = Graph.ensamblePonderateGraph_byFile(graphFileURL);
        Node actualNode = null;
        int actualNodePosition = 0;
        Edge selectedEdge = null;
        boolean finishAnt_Fail = false;
        boolean finishAnt_Success = false;
        boolean flagEnd = false;
        String input;
        int movementDoneCount = 0;
        float pheromoneTemp = 0.0f;
        ArrayList<Edge>finalPath = new ArrayList<Edge>();
        float pathDistance = 0.0f, minPathDistance=Float.MAX_VALUE;


        if(VERBOSE_MODE){
            System.out.println("Grafo inicial..:");
            graph.printGraphComplet();
        }

        do{
            for(int hormiga=0 ; hormiga<iterations ; hormiga++){
                
                    resetGraphValue(graph);
                    actualNodePosition = 0;
                    movementDoneCount = 0;
                    finishAnt_Fail = false;
                    finishAnt_Success = false;
                    actualNode = graph.getNode_byIndex(actualNodePosition);
                    finalPath = new ArrayList<Edge>();
                    pathDistance = 0.0f;
                
                do {    // Calculamos el recorido de una hormiga

                    // Paso 1: Verificamos si existe un camino disponible
                    graph.getNode_byIndex(actualNodePosition).setValue(0);
                    finishAnt_Fail = false;
                    finishAnt_Success = false;
                    if(!checkPosiblilities(graph, actualNode)){
                        if(checkCompleteGraph(graph)){
                            finishAnt_Success = true;
                        }else{
                            finishAnt_Fail = true;
                        }
                        break;
                    }


                    //Paso 2: Calculamos el proximo camino a recorrer
                    calculateEdgesProbability(graph, actualNode);


                    //Paso 3: Movemos a la hormiga
                    selectedEdge = selectNextMovement(actualNode);
                    finalPath.add(selectedEdge);

                    if(VERBOSE_MODE){
                        System.out.println("\n\nNº Hormiga: "+(hormiga+1)+"    nº movimiento "+(movementDoneCount+1));
                        System.out.println("posición actual: "+(actualNodePosition+1)+ "    posición siguiente: "+selectedEdge.getIdDestine());
                        graph.printGraphComplet();
                    }

                    graph.getNode_byIndex(actualNodePosition).setValue(1);
                    actualNode = graph.getNode_byIndex(selectedEdge.getIdDestine()-1);
                    actualNodePosition = selectedEdge.getIdDestine()-1;
                    movementDoneCount++;

                } while (!finishAnt_Fail && !finishAnt_Success); // Fin bucle de recorrido de hormigas
                

                //Paso 4: Actualización de feromonas
                if(finishAnt_Success){
                    pheromoneTemp = 0.0f;
                    for(int i=0 ; i<finalPath.size() ; i++){
                        pheromoneTemp = (1-rateEvaporationPheromone)*finalPath.get(i).getPheromone();
                        pheromoneTemp = pheromoneTemp + (1/finalPath.get(i).getDistance());
                        finalPath.get(i).setPheromone(pheromoneTemp);
                    }
                }


                //Paso 5: Imprimir resultados
                pathDistance=0; 
                for(int i=0 ; i<finalPath.size() ; i++){
                    pathDistance = pathDistance + finalPath.get(i).getDistance();
                }

                if(pathDistance < minPathDistance){
                    minPathDistance = pathDistance;
                    if(VERBOSE_MODE){
                        System.out.println("\n\nÚltimo movimiento..:");
                        System.out.println("Nº Hormiga: "+(hormiga+1)+"    nº movimiento "+(movementDoneCount+1));
                        System.out.println("posición actual: "+(actualNodePosition+1) +"    Posición siguiente: De vuelta a casa");
                        graph.printGraphComplet();
                        
                        if(finishAnt_Fail){
                            System.out.println("La hormiga no ha encontrado el camino. La pobre ha muerto de inanición.");
                        }else if(finishAnt_Success){
                            System.out.println("¡¡La hormiga ha logrado encontrar el camino!!. Será recordada como un heroe.");
                            printResult(finalPath, pathDistance);
                            break;
                        }       
                    }else{
                        System.out.println("\nNuevo camino más optimo encontrado..:");
                        System.out.println("Nº Hormiga: "+(hormiga+1)+"    nº movimiento "+(movementDoneCount+1));               
                        printResult(finalPath, pathDistance);
                    }
                }
                
            } // Fin bucle de iteraciones (hormigas)
                
            System.out.println("\n\nFINALIZACIÓN..:");
            System.out.println("Iteracion: " + iterations);
            System.out.println("Quiere realizar más interacciones? (S/n)..: ");
            do{
                input = sc.nextLine().toUpperCase();
                if (input.equals("S")) {
                    while (true) {
                        try {
                            System.out.println("Introduzca el número de nuevas iteraciones a realizar..: ");
                            iterations = iterations + sc.nextInt();
                            break;
                        } catch (Exception e) {
                            System.out.println("ERROR..: " + e.getMessage());
                        }
                    }
                    break;
                } else if(input.equals("N")){
                    flagEnd = true;
                    break;
                }
            }while(true);

        }while(!flagEnd);

        sc.close();
        return;
    }
    


    private static void resetGraphValue(Graph graph){
        for(int i=0 ; i<graph.getNodeList().size() ; i++){
            graph.getNode_byIndex(i).setValue(-1);
            for(int j=0 ; j<graph.getNode_byIndex(i).getEdgeList().size() ; j++){
                graph.getNode_byIndex(i).getEdge_byIndex(j).setProbably(0);
            }
        }
        return;
    }



    private static boolean checkPosiblilities(Graph graph, Node actualNode){

        for(int i=0 ; i<actualNode.getEdgeList().size() ; i++){
            if(graph.getNode_byIndex( actualNode.getEdge_byIndex(i).getIdDestine()-1).getValue() == -1){
                return true;
            }
        }
        return false;
    }



    private static boolean checkCompleteGraph(Graph graph){

        for(int i=0 ; i<graph.getNodeList().size() ; i++){
            if(graph.getNode_byIndex(i).getValue() == -1){
                return false;
            }
        }
        return true;
    }



    private static void calculateEdgesProbability(Graph graph,  Node node){
        float probablyTemp = 0.0f;
        float totalProbablyTemp = 0.0f;

        for(int i=0 ; i< node.getEdgeList().size() ; i++){
            
            if(graph.getNode_byIndex(node.getEdge_byIndex(i).getIdDestine()-1).getValue()!=-1){
                node.getEdge_byIndex(i).setProbably(0);          
            }else{
                probablyTemp = pheromoneControl * node.getEdge_byIndex(i).getPheromone();
                probablyTemp = probablyTemp * desirabilityControl * (1/node.getEdge_byIndex(i).getDistance());
                node.getEdge_byIndex(i).setProbably(probablyTemp);
                totalProbablyTemp = totalProbablyTemp +probablyTemp;
            }
        }

        node.setTotalProbablyEdges(0);
        for(int i=0 ; i< node.getEdgeList().size() ; i++){
            if(totalProbablyTemp==0 || node.getEdge_byIndex(i).getProbably()==0){
                node.getEdge_byIndex(i).setProbably(0);
            }else{
                node.getEdge_byIndex(i).setProbably(node.getEdge_byIndex(i).getProbably()/totalProbablyTemp);
                node.setTotalProbablyEdges(node.getTotalProbablyEdges()+node.getEdge_byIndex(i).getProbably());
            }
        }

        return;
    }



    private static Edge selectNextMovement(Node node){
        int positionSelected = 0;
        float randomSelection = (float)Math.random() * node.getTotalProbablyEdges();
        for(int i=0 ; i<node.getEdgeList().size() ; i++){
            if(randomSelection <= node.getEdge_byIndex(i).getProbably() && node.getEdge_byIndex(i).getProbably() > 0){
                positionSelected = i;
                break;
            }else{
                randomSelection = - node.getEdge_byIndex(i).getProbably();
            }
        }

        return node.getEdge_byIndex(positionSelected);
    }



    private static void printResult(ArrayList<Edge> list, float distance){
        
        System.out.print("Recorrido final ("+distance+")..: " +list.get(0).getIdSource()+" -> ");
        for(int i=0 ; i<list.size() ; i++){
            if(i==list.size()-1){
                System.out.print(list.get(i).getIdDestine()+"\n");
            }else{
                System.out.print(list.get(i).getIdDestine()+" -> ");
            }
        }
        System.out.print("Desglose de aristas..:");
        for(int i=0 ; i<list.size() ; i++){
            list.get(i).printEdgeComplet();
        }
        System.out.println();


        return;
    }



    private static Boolean checkInitialValues(String[] args) {

        if (args.length != 5) {
            System.out.println("Número de parámetros de entrada inválidos(" + args.length + "). La ejecución debe ser del tipo:");
            System.out.println("java main \"grafoURL\" \"Iteraciones\" \"ControlFeromonas\" \"ControlDeseabilidad\" \"tEvaporacionFeromonas\"");
            System.out.println("\tgrafoURL: Dirección dle archivo que contiene la definición del grafo.");
            System.out.println("\tIteraciones: Número de iteraciones a realizar (es decir, el número de hormigas).");
            System.out.println("\tControlFeromonas: Controla la influencia de las feromonas [0,1]");
            System.out.println("\tControlDeseabilidad: Controla la deseabilidad de los caminos [0,1]");
            System.out.println("\tEvaporacionFeromonas: Controla el ratio de evaporación de las feromonas [0,1]");
            return false;
        }
        System.out.println("Ejecución algoritmo `Ant Colony Optimization'. Parámetros:");
        System.out.println("\tDirección del grafo: " + args[0]);
        System.out.println("\tNúmero de iteraciones: " + args[1]);
        System.out.println("\tControl de feromonas: " + args[2]);
        System.out.println("\tControl de deseabilidad: " + args[3]);
        System.out.println("\tRatio de evaporación: " + args[4]);
        return true;
    }




}