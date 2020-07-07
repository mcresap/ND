#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>
using namespace std;
//introduce my functions
float angfunc(float, float);
float rfunc(float, float);
int quadfunc(float, float);
int main(){
float x=0;
float y=0;
float r=0;
float q=0;
int p=0; //what quadrant the point is in

	//recieve user input and reassign respective variables
	cout << "Enter x coordinate: " << endl;
	cin >> x;
	cout << "Enter y coordinate: " << endl;
	cin >> y;

	//call my functions for calculating the angle and radius and display results
	r=rfunc(x, y);
	q=angfunc(x, y);
	cout << "The polar radius is: " << fixed << setprecision(2) << r << endl;
	cout <<  "The polar angle is: " << q << " degrees from the x-axis." << endl;
	
	/*call function for determining what quadrant the point is in and return appropriate statement*/	
	p=quadfunc(x, y);

	if (p==1){
		cout << "This point is the origin." << endl;
	}
	else if (p==2){	
		cout << "This point is on the y axis." << endl;
	}
	else if (p==3){
		cout << "This point is on the x axis." << endl;
	}
	
	if (p==4)
		cout << "This point is in the first quadrant." << endl;
	if (p==5)
	        cout << "This point is in the third quadrant." << endl;
        if (p==6)
		cout << "This point is in the second quadrant." << endl;
	if (p==7)
		cout << "This point is in the fourth quadrant." << endl;

return 0;
}

//create function for calulating the polar radius
float rfunc(float x, float y){
float r=0;
	r=sqrt(pow(x, 2)+pow(y, 2));
//return variable r when function called in main function
return r;
}

//create function for calculating the polar angle
float angfunc(float x, float y){
float pi=0;
float q=0;
 	q=atan2(y,x);
	//calculate pi
        pi=atan2(0,-1);
	//convert angle to degrees
        q*=180/pi;
	//make all angles positive
	if (q<0){
		q=q+float(360);
		q=int(q)%360;
	}
//return variable q when function is called in the main function
return q;
}

//create a function for determining the quadrant the inputted point is in
int quadfunc(float x, float y){
int p=0;
	//check if (x, y) coordinate is on the x or y axis or the origin
	if (x==0 && y==0){
		p=1;
        }
        else if (x==0){ 
        	p=2; 
	}
        else if (y==0){ 
        	p=3; 
	}
	//check which quadrant the (x,y) point is in
	if (x>0 && y>0)
        	p=4; 
	if (x<0 && y<0)
                p=5;
	if (x<0 && y>0)
		p=6; 
        if (x>0 && y<0)
		p=7;
//return variable p when the function is called int he main function
return p;
}
