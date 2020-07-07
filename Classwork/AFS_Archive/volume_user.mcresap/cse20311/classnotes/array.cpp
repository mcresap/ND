#include <iostream>

using namespace std;

int main() {

int a[5], sum=0;
	for (int i=0; i<5; i++)
		a[i]=i*i;
	for (int i=0; i<5; i++)
		cout << a[i] << endl;
	for (int i=0; i<5;i++)
		sum+=a[i];
		cout << "the sum is: " << sum << endl;

return 0;
}
