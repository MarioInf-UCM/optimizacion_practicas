program.jar: main/Main.class world/World.class world/particle/Particle.class world/dimension/Dimension.class
	jar cmfv manifest $@ $^


dimensions = 2
iterations = 400
poblation = 25
inertiaFactor = 0.3925
personalFactor = 2.5586
grupalFactor = 1.3358




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
	java -jar program.jar $(dimensions) $(iterations) $(poblation) $(inertiaFactor) $(personalFactor) $(grupalFactor)

runFile:	
	java -jar program.jar $(URL) >> result/lastResult.txt
