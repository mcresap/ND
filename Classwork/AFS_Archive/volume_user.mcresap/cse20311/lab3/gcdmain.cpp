#include <iostream> 

using namespace std;

int getgcd(int , int );
int main(){
int a=0;
int b=0;
int gcd=0;
	//recieve user input 
	cout << "Enter two integers to find the GCD of them: " << endl;
	cin >> a >> b;
	//check if input is positive and make user enter positive integers
	if (a<=0){
		cout << "Enter two positive integers: " << endl;
		cin >> a >> b;
	}
	if (b<=0){
		cout << "Enter two positive integers: " << endl;
		cin >> a >> b;
	}
	//call my function getgcd to find the gcd of the entered integers
	gcd=getgcd(a, b);
	//display gcd to user
	cout << "Greatest common divisor: " << gcd << endl;

return 0;
}
//create program getgcd
int getgcd(int a, int b){
//initialize variable that will br returned to the user and into the main program (gcd)
int gcd=0;
	//check integers from 1 to the value of the larger inputted integer, incrementing by 1
	for (int i=1; i<=a && i<=b; i++){
		/*check remainder of inputted integer and current integer you're checking, if remainder is 0 then the current integer being checked is the gcd and this gets updated as integers being checked increase */
                if (a%i==0 && b%i==0){
                        gcd=i;
                }
        }
//return the variable "gcd" when this function is used in the main function
return gcd;
}
