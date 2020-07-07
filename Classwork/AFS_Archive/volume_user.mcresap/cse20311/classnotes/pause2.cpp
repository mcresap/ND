#include <iostream>

using namespace std;

int main() {

int n;
	cout << "enter a positive number: ";
	cin >> n;
	while (n<=0) {
 		cout << "error! ";
		cout << "enter a positive number: ";
		cin >> n;
	}

	cout << "it is " << n << endl;

return 0;
}
