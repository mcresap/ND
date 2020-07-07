#include <iostream>

using namespace std;

int main(){
	int length = 0, width = 0;
	// prompt user for input
	cout << "Enter length and width: " ;
	//read in input - length and width

	cin >> length;
	cin >> width;
	//check that input is collected/works

	//tell user what input was accepted
	cout << "You entered length: " << length << " and width: " << 
width << endl;
	// compare length and width
	cout << "Comparing (length < width): " << (length < width) << 
endl;
	cout << "(length*2 == width): " << (length*2 == width) << 
endl;
	bool result = false;
	result = (2*length == width);
	cout << "not result: " << !result << endl;

	// using and - && ; or - ||
	cout << "Length is between 0 and 10: " << ((0 < length) && 
(length < 10)) << endl;
	cout << "----------------------" << endl;
	if (0 < length){
		cout << "Length is positive! " << endl;
		if (length<10) {
			cout << " and length is less than 10." << endl;
		}
	}
	else if (length < 10){
		cout << "Length is less than 10!" << endl;
	}
	else {
		cout << "Length is negative!" << endl;
	}
	
	cout << "Nearing the end of the program!" << endl;
return 0;
}
