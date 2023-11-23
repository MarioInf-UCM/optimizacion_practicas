program.jar: main/Main.class world/World.class world/particle/Particle.class world/dimension/Dimension.class
	jar cmfv manifest $@ $^


dimensions = 2
iterations = 400
poblation = 13
crossover = 0.7450
DifferentialWeight = 0.9096

outputFile = ../result/lastResult.txt


main/Main.class: main/Main.java
	javac $^
	

world/World.class: world/World.java
	javac $^

world/particle/Particle.class: world/particle/Particle.java
	javac $^

world/dimension/Dimension.class: world/dimension/Dimension.java
	javac $^



clean:
	rm -f *.class

run:	
	java -jar program.jar $(dimensions) $(iterations) $(poblation) $(crossover) $(DifferentialWeight)

runFile:	
	java -jar program.jar $(dimensions) $(iterations) $(poblation) $(crossover) $(DifferentialWeight) > $(outputFile)
