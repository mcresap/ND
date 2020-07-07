#include <iostream>
#include <cstring>
using namespace std;

int main () {

    char c= 'f';
    int n=c;
    cout << c << endl;
    cout << n << endl;

    c=c+3;
    cout << c << endl;

    char word[20] = "hi there";
    cout << word << endl;
    word[5] = 'J';
    cout << word << endl;
    word[6] = 10;
    cout << word << endl; //10 corresponds to new line so replaces r with new line

    char str[28] = "I say hello! to you all";
    cout << str << endl;
    str[11] = 8; //8 performs a backspace
    cout << str << endl;

    for (int i=0; i<strlen(str); i++)
        str[i]++; /*every character will be replaces by the character after it adds 1 to its letter*/
    cout << str << endl;

    int m = c - 'a'; /*represents distance between this character and the beginning of the alphabet */
    cout << m << endl; //tells us i is the 8th letter of the alphabet

return 0;
}
