program.jar: src/main/Main.class src/graph/Graph.class src/graph/edge/Edge.class src/graph/node/Node.class src/kruskalAlgorithm/KruskalAlgorithm.class src/kruskalAlgorithm/kruskalEdge/KruskalEdge.class src/hierholzerAlgorithm/HierholzerAlgorithm.class src/hierholzerAlgorithm/hierholzerEdge/HierholzerEdge.class
	jar cmfv manifest $@ $^


graphFileURL = /home/mario/Documentos/universidad/optimizacion/ej5_algoritmoChristofides/dataPonderateGraph/berlin52.xml
outputFileURL = /home/mario/Documentos/universidad/optimizacion/ej5_algoritmoChristofides/result/lastResult.txt


src/main/Main.class: src/main/Main.java
	javac $^
	
src/hierholzerAlgorithm/HierholzerAlgorithm.class: src/hierholzerAlgorithm/HierholzerAlgorithm.java
	javac $^
src/hierholzerAlgorithm/hierholzerEdge/HierholzerEdge.class: src/hierholzerAlgorithm/hierholzerEdge/HierholzerEdge.java
	javac $^

src/kruskalAlgorithm/KruskalAlgorithm.class: src/kruskalAlgorithm/KruskalAlgorithm.java
	javac $^
src/kruskalAlgorithm/kruskalEdge/KruskalEdge.class: src/kruskalAlgorithm/kruskalEdge/KruskalEdge.java
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
	java -jar program.jar $(graphFileURL) $(iterations) 

runFile:	
	java -jar program.jar $(graphFileURL) $(iterations) > $(outputFileURL)
