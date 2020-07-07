#include <iostream>
using namespace std;
int main(){

    int n = 21; 
    do {
        switch(n%10) { 
            case 1:
            case 2:
            case 3:
                cout << "up" << endl;
                n++;
            case 4:
                cout << "jump" << endl;
                n *= 2;
                break; 
            default:
                cout << "down" << endl;
                n--;
                break;
        }
        cout << n << endl;
    } while( n%3 != 0 );

return 0;
}
