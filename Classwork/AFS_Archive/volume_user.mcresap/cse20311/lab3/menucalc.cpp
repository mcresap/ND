#include <iostream>
#include <cmath>
using namespace std;
//introduce functions to be created
double add(double, double);
double sub(double, double);
double mult(double,double);
double div(double, double);
int main() {

int choice=0;
double a=0;
double b=0;
double c=0;
	
	//ask user what they want to do
	cout << "What would you like to do?" << endl;
	cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
	cout << "3 for multiplication" << '\n' << "4 for division" << endl;
	cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
	cin >> choice;
	//make user enter a number between 1 and 5
	if (choice>5 || choice<1){
		cout << "What would you like to do?" << endl;
	        cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
        	cout << "3 for multiplication" << '\n' << "4 for division" << endl;
        	cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
        	cin >> choice;
	}
	//call appropriate function based on user input until user enters 5
	while (choice !=5){
		//call addition function
		if (choice==1){
			cout << "Enter two numbers: " << endl;
			cin >> a >> b;
			cout << "Inputs: " << a << ", " << b << endl;
			c=add(a, b);
			cout << "(" << a << ") + (" << b << ") = " << c << endl;
			//repeat prompt until user enters 5
			cout << "What would you like to do?" << endl;
       			cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
       			cout << "3 for multiplication" << '\n' << "4 for division" << endl;
        		cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
        		cin >> choice;
		}
		//call subtraction function
 		if (choice==2){
                	cout << "Enter two numbers: " << endl;
           	     	cin >> a >> b; 
           	     	cout << "Inputs: " << a << ", " << b << endl;
			c=sub(a, b);
                	cout << "(" << a << ") - (" << b << ") = " << c << endl;
        		//repeat prompting until user enters 5
			cout << "What would you like to do?" << endl;
       			cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
       			cout << "3 for multiplication" << '\n' << "4 for division" << endl;
		        cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
       			cin >> choice;
		}
		//call multiplication function
 		if (choice==3){
                	cout << "Enter two numbers: " << endl;
                	cin >> a >> b; 
                	cout << "Inputs: " << a << ", " << b << endl;
                	c=mult(a, b);
                	cout << "(" << a << ") * (" << b << ") = " << c << endl;
	    		//continue prompting until user enters 5
			cout << "What would you like to do?" << endl;
        		cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
       			cout << "3 for multiplication" << '\n' << "4 for division" << endl;
        		cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
        		cin >> choice;	
		} 
		//call division function
		if (choice==4){
                	cout << "Enter two numbers: " << endl;
            	    	cin >> a >> b; 
                	cout << "Inputs: " << a << ", " << b << endl;
			c=div(a,b);
        	        cout << "(" << a << ") / (" << b << ") = " << c << endl;
 	        	//continue prompting until user enters 5
			cout << "What would you like to do?" << endl;
        		cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
        		cout << "3 for multiplication" << '\n' << "4 for division" << endl;
        		cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
        		cin >> choice;
		}
		//make user enter an integer between 1 and 5
		if (choice>5 || choice<1){
	                cout << "What would you like to do?" << endl;
        	        cout << "1 for addition" << '\n' << "2 for subtraction" << endl;
               		cout << "3 for multiplication" << '\n' << "4 for division" << endl;
                	cout << "5 to exit" << '\n' << "Enter your choice: " << endl;
                	cin >> choice;
        	}
	}
	cout << "Thank you!" << endl;

return 0;
}
//create addition function
double add(double a, double b){
double c=0;
	c=a+b;
//return variable c when function called in main function
return c;
}
//create subtraction function
double sub(double a, double b){
double c=0;
	c=a-b;
//return variable c when function called in main function
return c;
}
//create multiplication function
double mult(double a, double b){
double c=0;
	c=a*b;
//return variable c when function called in main function
return c;
}
//create division function
double div(double a, double b){
double c=0;
	c=a/b;
//return variable c when function called in main function
return c;
}
