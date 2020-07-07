#include <iostream> 
using namespace std; 
int main()
{
    int a, b, n = 5, s = 0; 
    for (a = 1 ; a < n ; a++) 
        for (b = a ; b > 0 ; b--) 
            if (a != b) {
                s = s + a*b;
                cout << s << " " << a << " " << b << " ";
            }
    cout << endl;
}
