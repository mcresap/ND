#include <iostream>
using namespace std;
int main()
{
    int choice =0;
    cout << "Hello Emily." << endl;
    cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    cin >> choice;
    if (choice<1 || choice>3){
        cout << "Invalid choice Emily. Don't be stupid it's 1-3." << endl;
        cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    }
    if (choice==1)
        cout << "I'm sorry it's impossible for me to complement you." << endl;
    if (choice==2)
        cout << "Ya fake and ya boyfriend is a tool." << endl;
    if (choice==3)
        cout << "How many South Americans does it take to change a lightbuld?\nA Brazilian!!!!" << endl;


    return 0;
}
