//rational.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 1
//implementation for Rational class
#include <iostream>
using namespace std;
#include "rational.h"

//constructor: default rational object set to 1/1
Rational::Rational()
{
    denom=1;
    numer=1;
}

//constructor: when you want to specify what the numerator and denominator are
Rational::Rational(int n, int d)
{
    denom=d;
    numer=n;
}

//destructor
Rational::~Rational()
{ }

//returns the numerator
int Rational::getNumer()
{
    return numer;
}

//returns the denominator
int Rational::getDenom()
{
    return denom;
}

//changes the numerator
void Rational::setNumer(int n)
{
    numer=n;
}

//changes the denominator
void Rational::setDenom(int d)
{
    denom=d;
}

//prints the numerator and denominator to look like a fraction
void Rational::print()
{
    cout << getNumer() << "/" << getDenom() << endl;
}

//adds two rational numbers by making them have common denominators first
Rational Rational::add(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=b.getNumer()*denom+numer*(b.getDenom());
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//suntracts two rational numbers by making them have common denominators first
Rational Rational::subtract(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=numer*(b.getDenom())-b.getNumer()*denom;
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//multiplies two rational numbers
Rational Rational::multiply(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=b.getNumer()*numer;
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//divides two rational numbers
Rational Rational::divide(Rational b)
{
    int newdenom=denom*b.getNumer();
    int newnumer=numer*b.getDenom();
    Rational newrat(newnumer, newdenom);
    return newrat;
}
