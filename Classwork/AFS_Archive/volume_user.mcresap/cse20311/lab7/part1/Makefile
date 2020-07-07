# Makefile for the Rational class

runrational: rationalmain.o rational.o
	g++ rationalmain.o rational.o -o runrational

rationalmain.o: rationalmain.cpp rational.h
	g++ -c -std=c++11 rationalmain.cpp -o rationalmain.o

rational.o: rational.cpp rational.h
	g++ -c rational.cpp -o rational.o

clean:
	rm *.o runrational

