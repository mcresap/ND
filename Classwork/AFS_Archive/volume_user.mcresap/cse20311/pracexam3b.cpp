#include <iostream>
using namespace std;
int main(){

    for(int i = 20;i < 100;i++) { 
       
        if(i<50) 
            continue; 
        if(i%9==0) 
            break;
        cout << i << endl;
    }
return 0;
}
