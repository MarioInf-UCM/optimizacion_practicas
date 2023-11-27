program.jar: src/main/Main.class src/graph/Graph.class src/graph/edge/Edge.class src/graph/node/Node.class 
	jar cmfv manifest $@ $^


iterations = 1000
pheromoneControl = 1
desirabilityControl = 1
rateEvaporationPheromone = 0.5

graphFileURL = /home/mario/Documentos/universidad/optimizacion/ej4_AntColonyOptimization/dataPonderateGraph/graphCities5.gr
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
	java -jar program.jar $(graphFileURL) $(iterations) $(pheromoneControl) $(desirabilityControl) $(rateEvaporationPheromone)

runFile:	
	java -jar program.jar $(graphFileURL) $(iterations) $(pheromoneControl) $(desirabilityControl) $(rateEvaporationPheromone) > $(outputFileURL)
