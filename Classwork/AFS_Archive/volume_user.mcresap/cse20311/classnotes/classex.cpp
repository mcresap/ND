#include <iostream>
using namespace std;
#include <array>

const int size=5;
int main(){
    array<int, size> arr = {2, 16, 77, 34, 50};
    array<int, size>::iterator it;

    cout << "arr contains: ";
    for (it=arr.begin(); it< arr.end(); it++)
        cout << *it << " ";
    cout << endl;

    return 0;
}
