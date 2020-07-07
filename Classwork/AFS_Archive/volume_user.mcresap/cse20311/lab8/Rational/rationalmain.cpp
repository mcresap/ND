//rationalmain.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 1
//main function for Rational. Outputs all methods of Rational.
#include <iostream>
using namespace std;
#include <fstream>
#include "rational.h"

int main()
{
    //sets some rational numbers a, b, c, d, s
    Rational a, b, c, s, d, x, q;
    //asks for and prints rational numbers a, b, and c
    cin >> a;
    cout << "*** display a ***\n";
    //simplifies the fraction
    a.simplify();
    //makes the negative signs look better if applicable
    a.sign();
    cout << a;
    cout << "Numerator: " << a.getNumer() << endl << "Denominator: " << a.getDenom() << endl;
    cin >> b;
    cout << "*** display b ***\n";
    //simplifies the fraction
    b.simplify();
    //makes signs look better
    b.sign();
    cout << b;
    cout << "Numerator: " << b.getNumer() << endl << "Denominator: " << b.getDenom() << endl;
    cin >> c;
    cout << "*** display c ***\n";
    //simplifies c
    c.simplify();
    //makes signs of the fraction look better
    c.sign();
    cout << c;
    cout << "Numerator: " << c.getNumer() << endl << "Denominator: " << c.getDenom() << endl;

    //prints the sum of a and b
    cout << "*** compute s as the math of sum of a and b, and display s ***\n";
    s=a+b;
    //simplifies the fraction and checks for 0 denominator
    s.simplify();
    //checks the signs of the numerator and denominator to make it look better
    s.sign();
    cout << s;
    //displays the difference of b-a
    cout << "*** compute s as the math difference of b and a, and display d ***\n";
    d=b-a;
    //simplifies the fraction
    d.simplify();
    //makes the signs of the fraction look better
    d.sign();
    cout << d;
    //displays the product of a*c
    cout << "*** compute s as the product of a and c, and display x ***\n";
    x=a*c;
    //simplifies the multiplied rational numbers
    x.simplify();
    //fixes the signs to look better
    x.sign();
    cout << x;
    //displays the quotient of c/b
    cout << "*** compute s as the quotient of c and b, and display q ***\n";
    q=c/b;
    //simplifies the divided rational number
    q.simplify();
    //makes the signs of the number look better
    q.sign();
    cout << q;

    return 0;
}
