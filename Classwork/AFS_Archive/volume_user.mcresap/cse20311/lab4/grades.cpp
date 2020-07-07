//Maria Cresap
//CSE20311
//lab 4 grades.cpp
/*finds the average and standard deviation of grade values from a data file inputted into an array*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    //initialize array and variables
    int g[1000], i=0;
    float avg=0, sd=0, sum=0, x=0;
	//take input from input redirection/data file
    cin >> g[i];
    //loop until there is a sentinel value/negative number
	while (g[i]>0){
		/*calculate the total of all grades and increment i to move to the next element in the array which in inputted each loop*/
        sum+=g[i];
		i++;
		cin >> g[i];
	}
	/*calculate the average of the grades using the total of all the grades and the total number of grades*/
    avg=sum/i;
	//reset i to loop again to find the standard deviation
    i=0;
	//loop until there is a sentinel value/negative number
    while (g[i]>0){
        /*add up the current value minus the mean squared, for all elements in the array*/
		x+=pow((g[i]-avg),2);
		i++;
		cin >> g[i];
	}
    /*take the square root of the sum found in the previous loop and the total number of elements*/
	sd=sqrt((x/i));
    //display the average and standard deviation
	cout << "The average is: " << avg << endl; 
	cout << "The standard deviation is: " << sd << endl;

return 0;
}
