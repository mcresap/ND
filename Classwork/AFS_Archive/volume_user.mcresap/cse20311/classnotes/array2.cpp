#include <iostream>

using namespace std;

int main() {

int a[5], sum=0;
	
	cout << "enter 5 numbers: ";
	for (int i=0; i<5; i++){
		cin >> a[i];
		sum+=a[i];
	}
	cout << "the sum is: " << sum << endl;
	
return 0;
}
