// prob2.cpp
#include <iostream>
using namespace std;

int func1 (int, int &);
int func2 (int, int *);

int main()
{
  int x, y, z, w;

  x = 2;
  y = 7;

  cout << x << endl;
  cout << y << endl;

  cout << func1(x,y) << endl;
  cout << func2(x,&y) << endl;

  cout << x << endl;
  cout << y << endl;

  return 0;
}

int func1 (int a, int &b)
{
  a += 5;
  b += 2;
  return (a+b);
}

int func2 (int a, int *b)
{
  int c = *b;
  a += 3;
  c += 3;
  return (a+c);
}

