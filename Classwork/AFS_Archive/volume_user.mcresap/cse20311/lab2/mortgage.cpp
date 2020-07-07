#include <iostream>
#include <iomanip>
using namespace std;

int main() {

double intrate=0;
double monthlypay=0;
double principal=0;
double balance=0;
int month=1;
double interest=0;
double total=0;
int years=0;

	//ask user for inputs and set these values to the respective variables
        cout << "Enter the principal, interest rate, and desired monthly payment: " << endl;
        cin >> principal >> intrate >> monthlypay;
	//respond with an error if user inputs negative values for anything
	if (principal<0||intrate<0||monthlypay<0){
		cout << "Invalid input. Values must be positive." << '\n' << "Enter the ";
		cout << "principal, interest rate, and desired monthly payment: " << endl;

	}
	//respond with an error if user inputs a monthly pay that is too small
	if (principal*intrate<monthlypay){
		cout << "Desired payment is too small, balance will go up every month.";
		cout << "Enter the principal, interest rate, and desired monthly payment: ";
		cout << '\n';
	}
	//update the balance to the principle (initial balance)
	balance=principal;
	//reset the interest rate
	intrate=intrate/12;
	
	cout << setw(10) << "Month" << setw(18) << "Payment" << setw(18) << "Interest";
	cout << setw(18) << "Balance" << endl;

	//loop until the balance is less than or equal to the monthly pay
	while (balance>=monthlypay){
		//calculate the current interest to be displayed
		interest=balance*intrate;
		//update the balance to add the interest that needs to be paid
		balance=balance+interest;
		//update the total money paid
		total+=monthlypay;
		//update the balance after the monthly pay is paid
		balance=balance-monthlypay;
		//display necessary values
		cout << fixed <<  setprecision(2) << setw(10) << month;
		cout << fixed << setprecision(2) << setw(12) << "$" << monthlypay;
	 	cout << fixed << setprecision(2) << setw(12) << "$" << interest;
		cout << fixed << setprecision(2) << setw(12) << "$" << balance << endl; 
		//update the number of months that have passed
		month+=1;
	}
		/*repeat same things as in the loop for when the remaining balance in less 
than the monthly balance*/
		interest=intrate*balance;
		balance+=interest;
		monthlypay=balance;
		total+=monthlypay;
		balance=0;
		cout << setw(10) << month;
		cout << fixed << setprecision(2) << setw(12) << "$" << monthlypay;
                cout << fixed << setprecision(2) << setw(12) << "$" << interest;
                cout << fixed << setprecision(2) << setw(12) << "$" << balance << endl;
		
		//calculate the time passed
		years=month/12;
		month=month%12;
		cout << "You paid a total of $" << total << " over " << years << " years and " << month << " months.";

return 0;
}
