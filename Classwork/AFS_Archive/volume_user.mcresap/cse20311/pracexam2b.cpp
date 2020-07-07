#include <iostream>
using namespace std;
int main (){
    int a, b, c;
    a = 7;
    b = 6 + a--;
    c = b++ + --a;
    cout << a << " " << b << " " << c;



return 0;
}
