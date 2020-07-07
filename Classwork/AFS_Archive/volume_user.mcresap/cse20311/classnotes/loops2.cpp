#include <iostream>
using namespace std;

int main(){

	char answer='y';
	int counter=0;	

	while(answer=='y'){
		counter++;
		cout << "Your counter is: " << counter << endl;
		cout << "Continue? [y/n]: ";
		cin >> answer;
	}


return 0;
}
