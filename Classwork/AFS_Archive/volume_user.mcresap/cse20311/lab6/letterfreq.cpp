//Maria Cresap
//CSE 20311 - lab 6 - letterfreq.cpp
/*program counts the frequency of each letter of the alphabet as they occur in a text in a text file.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

int main(){
    string f, text;
    int space=0, total=0, let=0, r=0;
    double percent=0;
    char c;
    cout << "Enter the name of the text file: " << endl;
    cin >> f;
    //takes user's inputted file to use and opens it to "myfile"
    ifstream myfile;
    myfile.open(f);
    //checks if the file exists and outputs and error message if it does not
    if (!myfile){
        cout << "Error opening file " << f << endl;
        return 0;
    }
    /*creates a vector of 26 zeros where each element stores the frequency of a letter in the alphabet*/
    vector<int> letters(26, 0);
    //gets the first character in "myfile" and sets it to "c" char variable
    c=myfile.get();
    //goes through every character in the file
    while (!myfile.eof()){
        //increments the total characters
        total++;
        //checks if the character is a letter
        if (isalpha(c)) { 
            //sends the letters to lowercase
            c=tolower(c);
            //increments the element in letters that corresponds to the letter it is
            letters[(c)-97]++;
            //increments the appropriate letter element
            let++;
        }
        //checks if the character is a whitespace character
        else if (isspace(c))
            //increments the space counter
            space++;
        //gets the next character
        c=myfile.get();
    }
    //start with a using ascii numbers
    int l=97;
    //display the number of times each letter occurs
    for (auto it=letters.begin(); it!=letters.end(); it++){ 
        cout << setw(3) << fixed << (char) l++ << ":" << setw(6) <<*it ;
        r++;
        //display 6 letters per line
        if (r==6){
            cout << endl;
            r=0;
        }
    }
    cout << endl;
    //calculate the percent of white space out of the total number of characters
    percent=((double)space/(double)total)*100;
    //display the results
    cout << "there were " << let << " letters." << endl;
    cout << "there were " << total << " total characters." << endl;
    cout << "there were " << space << " white space characters." << endl;
    cout << "space percentage: " << setprecision(1) << fixed << percent << "%" << endl;

    return 0;
}
