#include <iostream> 
using namespace std;
int fun(int, int &); //prototype int main()
int main(){
    
    int a=5, b=6, n;
    n = fun(a, b);
    cout << a <<" "<< b <<" "<< n << endl; 
    b = 9;
    n = fun(8, b);
    cout << a <<" "<< b <<" "<< n << endl;
  
return 0;
}
int fun(int a, int &b) {
    int  n=7;
    a=1;
    b=2;
return (a+b); }
