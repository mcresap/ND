#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(){

double x=0;
double y;
int inc=.2;
double min=200;
double max=0;
double xmax=1;
double xmin=0;

	//display what is being graphed
	cout << "A plot of y=(cos(x)+2)*7 from x=0 to 17" << endl;
	//display top of x and y columns
	cout << setw(10) << "x" << setw(10) << "y" << endl;
		//loop for the domain (0-17) going up by .2 for x everytime you loop
		for (x=0;x<=17;x+=.2){
		 	//update y value for the current x value
			y=7*(cos(x)+2);
			//display current x and y values
			cout << fixed << setprecision(2) << setw(10) <<  x;
			cout << fixed << setprecision(2) << setw(10) << y << " ";
			//update variables min and max as you loop to find the min and max
			if (min>y){
				min=y;
				xmin=x;
			}
			if (max<y){
				max=y;
				xmax=x;
			}
			//draw the graph with #'s, rounding the y values
			for (int i=0;i<=y;i++){
				cout << "#";
	
			}
			cout << '\n';
		}
	//display the min and max values along with the x value they occur at
	cout << "The maximum of " << max << " was at x=" << xmax << endl;
	cout << "The minimum of " << min << " was at x=" << xmin << endl;



return 0;
}
