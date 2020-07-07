# Makefile for the State class

runstate: statemain.o state.o
	g++ statemain.o state.o -o runstate

statemain.o: statemain.cpp state.h
	g++ -c -std=c++11 statemain.cpp -o statemain.o

state.o: state.cpp state.h
	g++ -c state.cpp -o state.o

clean:
	rm *.o runstate

