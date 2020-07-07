#include <iostream>
using namespace std;
int main()
{
    int choice =0;
    cout << "Hello John." << endl;
    cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    cin >> choice;
    if (choice<1 || choice>3){
        cout << "Invalid choice John. Don't be stupid it's 1-3." << endl;
        cout << "Please choose what you want to do: \n1: be complemented\n2: be insulted\n3: hear a joke\n";
    }
    if (choice==1)
        cout << "You're a finance boner." << endl;
    if (choice==2)
        cout << "Only doofuses wear shorts with pockets." << endl;
    if (choice==3)
        cout << "Why can't you hear a pterodactyl going to the bathroom?\nBecause the P is silent." << endl;


    return 0;
}
