program.jar: main/Main.class graph/Graph.class graph/Node.class graph/Edge.class element/Element.class
	jar cmfv manifest $@ $^

main/Main.class: main/Main.java
	javac $^
	

graph/Graph.class: graph/Graph.java
	javac $^

graph/Node.class: graph/Node.java
	javac $^

graph/Edge.class: graph/Edge.java
	javac $^


element/Element.class: element/Element.java
	javac $^



clean:
	rm -f *.class

run:	
	java -jar program.jar 20 50 

runFile:	
	java -jar program.jar 20 50 >> result/lastResult.txt
