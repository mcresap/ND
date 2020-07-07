#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){

    int n=10;
    srand(time(NULL));
    for (int i=1; i<=n; i++){
        cout << rand()%50+1 << endl;
    }
    return 0;
}
