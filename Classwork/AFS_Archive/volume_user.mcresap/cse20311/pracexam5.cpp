#include <iostream>

using namespace std;
double myexp(double);
int main (){
    double term=1, ex=0;
    int n=0;

    myexp(term);
    cout << ex;







return 0;
}
double myexp(double term){
    double  ex=0;
    int n=0;
    while (term >0.001){
        ex+=term;
        n++;
        term*=term/n;
    }
return ex;
}
