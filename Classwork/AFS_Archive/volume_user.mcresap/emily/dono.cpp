#include <iostream>
using namespace std;
int main()
{
    int choice =0;
    cout << "Hello Alex." << endl;
    cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    cin >> choice;
    if (choice<1 || choice>3){
        cout << "Invalid choice Alex. Don't be stupid it's 1-3." << endl;
        cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    }
    if (choice==1)
        cout << "You have an nice head of hair. Lol." << endl;
    if (choice==2)
        cout << "You a hoe." << endl;
    if (choice==3)
        cout << "How many South Americans does it take to change a lightbuld?\nA Brazilian!!!!" << endl;


    return 0;
}