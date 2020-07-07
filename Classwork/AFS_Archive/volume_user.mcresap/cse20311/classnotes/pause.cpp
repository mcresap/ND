#include <iostream>

using namespace std;

int main() {

int n;

	do {
		cout << "enter a positive number: ";
		cin >> n;
		if  (n<=0)
			cout << "error! ";
	} while (n<=0);

	cout << "it is " << n << endl;

return 0;
}
