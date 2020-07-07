#include <iostream>
#include <cmath> // for pow function
#include <math.h> // for sqrt function
using namespace std;

int main() 
{
double x1;
double x2;
double a;
double b;
double c;

	cout << "Let's find the roots of a quadratic! " << endl;
	cout << "What is your a value? ";
	cin >> a;
	cout << "What is your b value? ";
	cin >> b;
	cout << "What is your c value? ";
	cin >> c;

	x1 = (-b+sqrt((pow(b,2)-4*a*c)))/(2*a);
	x2 = (-b-sqrt((pow(b,2)-4*a*c)))/(2*a);

	cout << "The roots of your equation are " << x1 << " and " << x2 << endl;




return 0;
}

