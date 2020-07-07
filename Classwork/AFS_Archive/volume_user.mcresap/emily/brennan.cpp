#include <iostream>
using namespace std;
int main()
{
    int choice =0;
    cout << "Hello Nan." << endl;
    cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    cin >> choice;
    if (choice<1 || choice>3){
        cout << "Invalid choice Brennan. Don't be stupid it's 1-3." << endl;
        cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    }
    if (choice==1)
        cout << "You're a standup guy." << endl;
    if (choice==2)
        cout << "You're so sensitive." << endl;
    if (choice==3)
        cout << "Did you hear about the constipated mathematician?\nHe worked his problem out with a pencil...a number 2 pencil" << endl;


    return 0;
}
