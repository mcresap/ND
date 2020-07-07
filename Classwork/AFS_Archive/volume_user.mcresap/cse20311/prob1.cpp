// prob1.cpp
#include <iostream>
#include <vector>
using namespace std;
void func1 (int []);
void func2 (vector<int>);

int main()
{
  char s[] = "Notre Dame", *p = s;
  int a[] = {1, 4, 8};
  vector<int> v = {3, 4, 5};

  cout << *p << endl;
  cout << p << endl;
  
  func1(a);
  func2(v);
  cout << a[0] << " " << a[1] << " " << a[2] << endl;
  cout << v[0] << " " << v[1] << " " << v[2] << endl;

  return 0;
}

void func1 (int x[])
{
  x[0]++; x[1]++; x[2]++;
}

void func2 (vector<int> x)
{
  x[0]++; x[1]++; x[2]++;
}

