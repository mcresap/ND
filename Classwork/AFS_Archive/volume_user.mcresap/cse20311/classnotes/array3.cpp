#include <iostream>

using namespace std;
//
int main() {

int a[20], i=0, sum=0;
	
	cout << "enter some positive numbers (max of 19), followed by a -1: ";
	cin >> a[i];
	while (a[i]>0){
		sum+=a[i];
		i++;
		cin >> a[i]; //-1 gets read in and is in a
	}
	cout << "the sum is: " << sum << endl;
	cout << "there are " << i << " numbers."; 
//use i because when -1 is read in i has already been incremented

return 0;
}
