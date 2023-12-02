program.jar: src/main/Main.class src/graph/Graph.class src/graph/edge/Edge.class src/graph/node/Node.class 
	jar cmfv manifest $@ $^


graphFileURL = /home/mario/Documentos/universidad/optimizacion/ej1_matchingMaximal/data/vc-exact_087.gr
outputFileURL = /home/mario/Documentos/universidad/optimizacion/ej1_matchingMaximal/result/resultado.txt


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
	java -jar program.jar $(graphFileURL)

runFile:	
	java -jar program.jar $(graphFileURL) > $(outputFileURL)
