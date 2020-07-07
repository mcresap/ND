#include <iostream>
using namespace std;
#include <string>
#include <fstream>

int main(){
    ifstream ifs;
    string thefile;

    cout << "Enter file name: ";
    cin >> thefile;

    ifs.open(thefile);
        if (!ifs){ //if null character kick out
            cout << "error" << endl;
            return 1;
        }

        int n;
        int i=0;
        ifs >> n;
        while (!ifs.eof()){
            i++;
            cout << i << ": " << n << endl;
            ifs >> n;
        }
        return 0;
}
