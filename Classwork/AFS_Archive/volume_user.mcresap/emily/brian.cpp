#include <iostream>
using namespace std;
int main()
{
    int choice =0;
    cout << "Hello Mr. Finn." << endl;
    cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    cin >> choice;
    if (choice<1 || choice>3){
        cout << "Invalid choice Brian. Don't be stupid it's 1-3." << endl;
        cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    }
    if (choice==1)
        cout << "You wear nice issued gear." << endl;
    if (choice==2)
        cout << "You're not a real athlete." << endl;
    if (choice==3)
        cout << "What does batman get in his drinks?\nJust ice!" << endl;


    return 0;
}
