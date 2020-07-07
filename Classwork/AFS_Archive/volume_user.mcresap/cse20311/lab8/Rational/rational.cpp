//rational.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 1
//implementation for Rational class
#include <iostream>
using namespace std;
#include <fstream>
#include <cmath>
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
//sets rational number
void Rational::setRat(int n, int d)
{
    setNumer(n);
    setDenom(d);
}

//prints the numerator and denominator to look like a fraction
ostream& operator<<(ostream &f, Rational &s)
{
    f << s.getNumer() << "/" << s.getDenom() << endl;
    return f;
}
//overloads input operator
istream& operator>>(istream &f, Rational &s)
{
    int n, d;
    cout << "Enter the numerator and denominator: ";
    f >> n >> d;
    s.setRat(n, d);
    return f;
}

//adds two rational numbers by making them have common denominators first
//overloaded addition operator
Rational Rational::operator+(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=b.getNumer()*denom+numer*(b.getDenom());
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//suntracts two rational numbers by making them have common denominators first
//overloaded - operator
Rational Rational::operator-(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=numer*(b.getDenom())-b.getNumer()*denom;
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//multiplies two rational numbers
//overloaded * operator
Rational Rational::operator*(Rational b)
{
    int newdenom=b.getDenom()*denom;
    int newnumer=b.getNumer()*numer;
    Rational newrat(newnumer, newdenom);
    return newrat;
}

//divides two rational numbers
//overloaded / operator
Rational Rational::operator/(Rational b)
{
    int newdenom=denom*b.getNumer();
    int newnumer=numer*b.getDenom();
    Rational newrat(newnumer, newdenom);
    return newrat;
}
/*changes sign of rational number if numerator and denominator are both negative or denominator is negative to make fractions look better*/
void Rational::sign()
{
    if (numer<0 && denom<0){
        numer=-numer;
        denom=-denom;
    }
    if (denom<0){
        denom=-denom;
        numer=-numer;
    }
}
//simplifies fractions 
void Rational::simplify()
{   
    //makes sure denominator isn't 0
    if (denom==0){
        cout << "Undefined." << endl;
    }
    else {
        //calculates gcd of numerator and denominator
        int gcd=0;
        for (int i=1; i<=abs(numer) && i<=abs(denom); i++){
            if (numer%i==0 && denom%i==0){
                gcd=i;
            }
        }
        //makes sure gcd isn't 0 because would cause a 0 denominator
        if (gcd!=0){
            //reduces fraction 
            numer=numer/gcd;
            denom=denom/gcd;
        }
        //if numerator 0, whole fraction is 0
        if (numer==0){
            numer=0;
            denom=0;
        }
    }
}
