// testmyint.cpp
#include <iostream>
using namespace std;

#include "myint.h"

int main()
{
  MyInt a, b(5);

  cout << "a is " << a.getValue() << endl;
  cout << "b is " << b.getValue() << endl;
  a.setValue(44);
  cout << "a is now " << a.getValue() << endl;

  MyInt c = a + b;  //  "+" is overloaded
  MyInt d = a - b;  //  "-" is overloaded
  cout << "a+b is " << c.getValue() << endl;
  cout << "a-b is " << d.getValue() << endl;

  return 0;
}

