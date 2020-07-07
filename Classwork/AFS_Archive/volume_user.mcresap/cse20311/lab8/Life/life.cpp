//Maria Cresap
//life.cpp 
//CSE 20311 Lab 8
//dirver for Lifeboard class
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include "lifeboard.h"
//prototypes
void interactive();
void batch(char*);
void view(Lifeboard &, char);

using namespace std;
//main function
int main (int argc, char** argv)
{
    switch (argc) { //determines the mode based on the number of inputs
        case 1: //no file: interactive mode
            interactive();
            break;
        case 2: //scene file: batch mode
            batch (argv[1]);
            break;
        default: //more than 2 inputs gets an error
            cout << "Invalid number of arguments." << endl;
            break;
    }
    return 0;
}
//functions
//interactive mode function for the user to play
void interactive()
{
    char choice;
    Lifeboard board=Lifeboard();
    //continues to prompt until user enters q
    do 
    {
        board.display();
        cout << "Enter an a(add), r(remove), n(next iteration), p(play continuously), or q(quit) : "; //to prompt the user to enter a choice for activites
        cin >> choice;
        view(board, choice);
    }
    while (choice!='q');
}

void batch(char* file)
{
    //gets scene file
    ifstream ifs;
    string line, str="";
    Lifeboard board=Lifeboard();
    int r, c, i;
    //opens scene file with p an sentinel value
    ifs.open(file);
    getline(ifs, line);
    while (line!="p")
    {
        str="";
        i=2;
        while (line[i]!=' '){
            str+=line[i];
            i++;
        }
        //turns the string 'str' into an integer 'r' and nulls the string
        r=stoi(str);
        str="";
        i++;
        while (line[i]!=' '){
            str+=line[i];
            i++;
        }
        //turns the string 'str' into an integer 'c'
        c=stoi(str);
        board.setSpacePos(r, c);
        getline(ifs, line);
    }
    //closes the scene file
    ifs.close();
    while (true){
        //displays the board and advances the scenes and slows down the speed so the animation is visible
        board.display();
        board.advance();
        usleep(100000);
    }
}

void view(Lifeboard &board, char choice)
{
    int r, c;
    
    switch (choice){
        //creating a cell
        case 'a':
            cout << "Enter the row of the new cell: ";
            cin >> r;
            cout << "Enter the column of the new cell: ";
            cin >> c;
            //verifies users entry is valid
            if (c<40 && c>0 && r<40 && r>0){
                board.setSpacePos(r-1, c-1);
            }
            else
                cout << "Not a valid point." << endl;
            break;
        //deleting a cell
        case 'r':
            cout << "Enter the row of the cell to kill: ";
            cin >> r;
            cout << "Enter the column of the cell to kill: ";
            cin >> c;
            
            if (c<40 && c>0 && r<40 && r>0){
                board.setSpaceNeg(r-1, c-1);
            }
            else
                cout << "Not a valid point." << endl;
            break;
        //advancing to next generation
        case 'n':
            board.advance();
            break;
        //plays board continuously
        case 'p':
            while (true){
                //displays the board and advances and slows down the animation so it is visible
                board.advance();
                board.display();
                usleep(100000);
            }
            break;
        //quits the program
        case 'q':
            break;
        //checks user's entry is a valid choice
        default:
            cout << "Invalid Selection." << endl;
            break;
    }

}

