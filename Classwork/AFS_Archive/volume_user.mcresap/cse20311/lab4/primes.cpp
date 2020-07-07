//Maria Cresap
//CSE20311 
//Lab 4, primes.cpp
/*uses an array of 1000 elements to find all the prime numbers between 2 and 999*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    //initialize array with 1000 elements
    int a[1000], x=0;
    //initialize all values of the array to be 1
    for (int i=1; i<1000; i++)
        a[i]=1;   
   //loop from 2 to the square root on 1000, incrementing each loop 
	for (int i=2; i<sqrt(1000); i++) {
        //loop through every element in a because all elements were set to 1
		if (a[i]==1){
            /*set values that are multiples of the current value to 0. This loop increments by i^2+j*i where j starts as 0 and increments each loop*/
		    for (int j=0; (pow(i, 2)+j*i)<1000; j++){
			    a[(int)(pow(i,2)+j*i)]=0;
            }
		}
	}
    //display all elements of the array that have a value of 1
	for (int i=2; i<1000; i++){
		if (a[i]==1){
            //display the which elements have value 1
			cout << i << "\t" << setw(2);
            x+=1;
            //display prime numbers with 10 per row
            if (x==10){
                cout << "\n";
                x=0;
            }
        }
	}
    cout << "\n";
return 0;
}
