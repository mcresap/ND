#include <iostream>
using namespace std;
#include "money.h"

int main()
{
    Money m1(4, 92), m2;
    cout << "m1's amount is: " << m1 << endl;
    cout << "Getting m2's values:\n";
    cin >> m2;
    cout << "m2's amount is: " << m2 << endl;

    Money f=m1 +m2;
    cout << "Sum of m1 and m2 is: " << f << endl;

    Money g=m1>m2 ? m1-m2 : m2-m1;
    cout << "Difference between m1 and m2: ";
    cout << g << endl;
    return 0;
}
