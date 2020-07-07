#include <iostream>

using namespace std;

int main() {

int n, sum=0;
	
	cout << "Enter 5 numbers: ";
	
	for (int i=1; i<=5; i++) {
		cin >>n;
		sum+=n;
	}
	
	cout << "The sum is " << sum << endl;

return 0;
}
