all: Main.class

Main.class: /usr/bin/java Main.java
		javac Main.java && java Main

Race.class: /usr/bin/java Race.java RaceStrategy.java Horse.java
		javac Race.java && javac RaceStrategy.java && javac Horse.java

Horse.class: /usr/bin/java Horse.java
		javac Horse.java

RaceStrategy.class: /usr/bin/java RaceStrategy.java
		javac RaceStrategy.java

Slow.class: /usr/bin/java Slow.java
		javac Slow.java

Steady.class: /usr/bin/java Steady.java
		javac Steady.java

Sprint.class: /usr/bin/java Sprint.java
		javac Sprint.java

HorseTest.class: /usr/bin/java HorseTest.java
		@export CLASSPATH=.:/usr/share/java/junit4.jar || setenv CLASSPATH ".:/usr/share/javajunit4.jar" && javac HorseTest.java

test: Race.class HorseTest.class
		java -cp .:/usr/share/java/junit.jar org.junit.runner.JUnitCore HorseTest

clean:
		rm -rf *.class
