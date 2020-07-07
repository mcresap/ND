//state.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 2
//implamentation for State
#include <iostream>
#include <ctype.h>
#include "state.h"

//constructor: default object set to alabama
State::State()
{
    abbreviation="AL"; name="Alabama"; capital="Montgomery"; population=4859000; year=1819; reps=7;
}
//constructor: when you want to specify the object/state
State::State(string abbrv, string n, string cap, int pop, int yr, int r)
{
    abbreviation=abbrv; name=n; capital=cap; population=pop; year=yr; reps=r;
}
//destructor
State::~State()
{ }
//returns a state's abbreviation
string State::getAbbrev()
{
    return abbreviation;
}
//returns the name
string State::getName()
{
    return name;
}
//returns the capital
string State::getCapital()
{
    return capital;
}
//returns the population
int State::getPop()
{
    return population;
}
//returns the year founded
int State::getYear()
{
    return year;
}
//returns the number of representatives
int State::getReps()
{
    return reps;
}

void State::setAbbrev(string abbrv)
{
    abbreviation=abbrv;
}

void State::setName(string n)
{
    name=n;
}

void State::setCapital(string cap)
{
    capital=cap;
}

void State::setPop(int pop)
{
    population=pop;
}

void State::setYear(int yr)
{
    year=yr;
}

void State::setReps(int r)
{
    reps=r;
}
//prints a certain state's information
void State::print()
{
    cout << "Abbreviation: " << abbreviation << "\nName: " << name << "\nCapital: " << capital << "\nPopulation: " << population << "\nYear: " << year <<"\nRepresentatives: " << reps << endl;
}
//checks if the population of a state is over a certain number and returns true if it is or false if not
bool State::popOver(int x)
{
    if (x<population)
        return true;
    else if (x>=population)
        return false;
}
//checks if the year founded is over a certain number
bool State::yearOver(int x)
{
    if (x<year)
        return true;
    else if (x>=year)
        return false;
}
//calculates the ratio of the number of reps to the population of a state
double State::ratios()
{
    return (double)reps/(double)population;
}
//makes the state name lowercase
string State::getLower()
{
    string lowername=name;
    for (int i=0; i<lowername.length(); i++)
        lowername[i]=tolower(lowername[i]);
    return lowername;
}

