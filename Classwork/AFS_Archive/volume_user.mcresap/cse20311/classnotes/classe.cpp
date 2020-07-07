#include <iostream>
using namespace std;
#include <array>

const int size=5;

int main(){
    array<int, size> arr = {2, 16, 77, 34, 50};
    cout << "arr contatins: ";
    for (int i=0; i<arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
