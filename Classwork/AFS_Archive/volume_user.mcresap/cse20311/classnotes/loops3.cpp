#include <iostream>

using namespace std;

int main(){
//predicting when future tuition will double
	double tuition=100000;
	double rate=1.07;
	int year=1;

	cout << "Year     Tuition" << endl;
	cout << "_______________" << endl;
	while(tuition<200000){
		tuition=tuition*rate;
		cout << year << "        " << tuition<< endl;
		year++;
	}
	
	cout << "Tuition exceeds double after " << (year-1) << " years." 
<< 
endl;


return 0;
}
