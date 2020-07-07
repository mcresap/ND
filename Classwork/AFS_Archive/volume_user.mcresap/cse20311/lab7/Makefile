# Makefile for testing the Circle class

runcircle: testcircle.o circle.o
	g++ testcircle.o circle.o -o runcircle

testcircle.o: testcircle.cpp circle.h
	g++ -c testcircle.cpp -o testcircle.o

circle.o: circle.cpp circle.h
	g++ -c circle.cpp -o circle.o

clean:
	rm *.o runcircle

