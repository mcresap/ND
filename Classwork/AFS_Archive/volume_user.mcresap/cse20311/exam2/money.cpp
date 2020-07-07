#include <iostream>
using namespace std;
#include "money.h"

Money::Money()
{ 
    dollar=3;
    cent = 52;
}
Money::Money(int d, int c)
{
    dollar=d;
    cent=c;
}
Money::~Money()
{}
int Money::getDollar()
{ return dollar; }
int Money::getCent()
{ return cent; }
void Money::setDollar(int d)
{
    dollar=d;
}
void Money::setCent(int c)
{ cent=c; }
void Money::setMoney(int d, int c)
{
    //c.convert();
    setDollar(d);
    setCent(c);
}
void Money::convert()
{
    if (cent>99){
        cent=cent%100;
        dollar=dollar+cent/100;
    }
}
Money Money::operator+(Money m)
{
    int newdoll=m.getDollar() + dollar;
    int newcent=m.getCent() + cent;
    Money newmon(newdoll, newcent);
    return newmon;
}
Money Money::operator-(Money m)
{
    int newdoll=m.getDollar() - dollar;
    int newcent=m.getCent() - cent;
    Money newmon(newdoll, newcent);
    return newmon;
}
bool Money::operator>(Money m)
{
    
}
ostream& operator<<(ostream &f, Money &m)
{
    f << "$" << m.getDollar() << "." << m.getCent();
}
istream& operator>>(istream &e, Money &m)
{
    int c, d;
    e >> d >> c;
    m.setMoney(d, c);
    return e;
}
