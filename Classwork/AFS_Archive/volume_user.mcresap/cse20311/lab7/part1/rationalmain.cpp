//rationalmain.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 1
//main function for Rational. Outputs all methods of Rational.
#include <iostream>
using namespace std;

#include "rational.h"

int main()
{
    //sets some rational numbers a, b, c, d, s
    Rational a(5, 6), b(3,7), c, s, d(-2, 8);
    //prints rational numbers a and b
    cout << "*** display a and b ***\n";
    a.print();
    b.print();
    //prints rational number c
    cout << "*** display c ***\n";
    c.print();
    //prints the sum of a and b
    cout << "*** compute s as the math of sum of a and b, and display s ***\n";
    s=a.add(b);
    s.print();
    //displays the difference of b-a
    cout << "*** compute s as the math difference of b and a, and display s***\n";
    s=b.subtract(a);
    s.print();
    //displays the product of a*d
    cout << "*** compute s as the product of a and d, and display s***\n";
    s=a.multiply(d);
    s.print();
    //displays the quotient of d/b
    cout << "*** compute s as the quotient of d and b, and display s***\n";
    s=d.divide(b);
    s.print();


    return 0;
}
