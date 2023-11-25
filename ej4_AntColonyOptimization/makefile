program.jar: src/main/Main.class src/graph/Graph.class src/graph/edge/Edge.class src/graph/node/Node.class 
	jar cmfv manifest $@ $^


iterations = 400
pheromoneControl = 1
desirabilityControl = 1

graphFileURL = /home/mario/Documentos/universidad/optimizacion/ej4_AntColonyOptimization/dataPonderateGraph/vc-exact_005.gr
outputFileURL = /home/mario/Documentos/universidad/optimizacion/ej4_AntColonyOptimization/result/lastResult.txt


src/main/Main.class: src/main/Main.java
	javac $^
	

src/graph/Graph.class: src/graph/Graph.java
	javac $^

src/graph/edge/Edge.class: src/graph/edge/Edge.java
	javac $^

src/graph/node/Node.class: src/graph/edge/Edge.java
	javac $^




clean:
	find . -type f -name '*.class' -delete

run:	
	java -jar program.jar $(graphFileURL) $(iterations) $(pheromoneControl) $(desirabilityControl)

runFile:	
	java -jar program.jar $(graphFileURL) $(iterations) $(pheromoneControl) $(desirabilityControl) > $(outputFileURL)
