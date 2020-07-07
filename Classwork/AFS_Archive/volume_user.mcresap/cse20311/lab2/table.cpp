#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
int r, c;

	//ask user for table size
	cout << "What size table would you like to see? (2 integers)" << 
endl;
	cin >> c >> r;
		//loop for every row
	for (int i=0; i<r+1;i++)			
	{
		//loop for every column in each row
		for (int j=0; j<c+1;j++) {
			//set the top left corner to a *
			if (i==0 && j==0)
				cout << "*" << '\t';
			//set the top row to the value being multiplied
			else if (i==0)
				cout << j << '\t';	
			//set the first column to the value being mult
			else if (j==0) 
				cout << i << '\t';
			//set the values in the table to the muliples
			else
				cout << i*j << '\t';
		}
		//start each row on a new line
		cout << endl;
	}

return 0;
}
