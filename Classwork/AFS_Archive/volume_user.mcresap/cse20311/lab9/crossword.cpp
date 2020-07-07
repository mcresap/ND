//Maria Cresap
//crossword.cpp
//CSE 20311 Lab 9
//driver/main file for crossword
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "board.h"
void interactive();
void infile(char*);
void outfile(char*, char*);
void view(Board &, char);
using namespace std;

int main (int argc, char* argv[])
{
    switch (argc){
        case 1: //no file interactive mode
            interactive();
            break;
        case 2: //input from a file mode
            infile(argv[1]);
            break;
        case 3: //inout from file output to file mode
            outfile(argv[1], argv[2]);
            break;
        default: //more than 3 inputs gets an error
            cout << "Invalid number of arguments." << endl;
            break;
    }
    return 0;
}
//functions
//interactive mode function
void interactive()
{
    string inword;
    vector<string> words={" "};
    vector<string> anagramval, horizontalval;
    vector<int> rvals, cvals;
    Board crossboard;
    //prompt user to input words
    cout << "Enter up to 20 words of up to 15 letters each ending with a period: " << endl;
    cin >> inword;//takes in each word in the string variable "inword"
    while (inword != "."){//takes in words until it reaches a period
        if (inword.length() <= 15){ //makes sure words isn't longer than 15 characters
            for (int i=0; i<inword.length(); i++) {
                inword[i]=toupper(inword[i]);//converts all letters to uppercase
            }
        auto it = words.begin();
        while (it != words.end() && inword.length() < it->length()) {
            ++it;//places words into "words" vector by length
        }
        words.insert(it, inword);//adds current word to vector of strings "words" which stores all the words
        anagramval.push_back(crossboard.anagram(inword));//adds current word to vector of strings "anagramval" to have their letters shuffled later to be used as hints
        }
        else
            cout << "The word you entered is too long. Enter a shorter word." << endl;//returns appropriate error if words are too long
        cin >> inword;
    }
    crossboard.placeFirst(words[0]); //places logest word/first word onto the board
    //stores row and column value of longest word
    rvals.push_back(crossboard.getRow());
    cvals.push_back(crossboard.getCol());
    horizontalval.push_back("Across");//stores orientation of first word (which is always horizontal)

    auto it =words.begin();//goes through all of the other words
    advance(it, 1);
    //places the rest of the words on the board
    for (it; it!=words.end(); ++it){
        crossboard.placeNext(*it);
        //store row and column values of word placements
        rvals.push_back(crossboard.getRow());
        cvals.push_back(crossboard.getCol());
        if (crossboard.getHA()==true)
            horizontalval.push_back("Down");//records the orientation of each word to be used in hints later
        else 
            horizontalval.push_back("Across");
    }
    crossboard.print();//uses the print method to print the solution and empty board
    cout << "Clues: " << endl;//prints the clues
    cout << endl;
    int size=rvals.size();

    for (int it = size-2; it>=0; --it){
        cout << setw(8) << rvals[it] << ", " << cvals[it];
        cout << setw(8) << horizontalval[it] << setw(18) << anagramval[it] << endl;
    }
}
//using input from a file and outputs regularly
void infile(char* file)
{   
    string inword;
    vector<string> words={" "};
    vector<string> anagramval, horizontalval;
    vector<int> rvals, cvals;
    //gets file for the input
    ifstream ifs(file);
    ifs >> inword;//takes in each word of the file
    Board crossboard;
    if (!ifs){ //checks that the input file exists
        cout << "Error opening file " << file << endl;
        return;
    }
    while (!ifs.eof()){//goes through the whole file
        if (inword!="."){//until it reaches a period
            if (inword.length() <= 15){ //makes sure word isn't longer than 15 characters
                for (int i=0; i<inword.length(); i++){//convert all letters to uppercase
                    inword[i]=toupper(inword[i]);
                }
                auto it = words.begin();
                while (it !=words.end() && inword.length() < it->length()) 
                    ++it; //puts words in vector by length
                words.insert(it, inword);//add the current word to the vector of strings "words" that is storing all of the words
                anagramval.push_back(crossboard.anagram(inword));//add the current word to the vector of strings "anagramval" that is storing all the words to have their letters shuffled later to use as hints
            }
            else
                cout << "One of the words in your file is too long." << endl;//returns appropriate error if word in file is too long
        }
        ifs >> inword;
    }
    crossboard.placeFirst(words[0]);//uses placeFirst method to place the first word
    rvals.push_back(crossboard.getRow());//records the position of the first letter of the first word
    cvals.push_back(crossboard.getCol());
    horizontalval.push_back("Across");//records the orientation of the first word which is always horizontal

    auto it = words.begin();//goes through all the words
    advance(it, 1);
    for (it; it != words.end(); ++it){
        crossboard.placeNext(*it); //places the rest of the words on the board using the placeNext method
        rvals.push_back(crossboard.getRow()); //store row and column positions of the first letter of the words
        cvals.push_back(crossboard.getCol());
        if (crossboard.getHA() == true)//records the orientation of words to add to clues later
            horizontalval.push_back("Down");
        else 
            horizontalval.push_back("Across");
    }
    crossboard.print();//prints out the output using the 'print' method
    cout << "Clues:" << endl; //prints out the clues
    cout << endl;
    int size = cvals.size();
    for (int j = size-2; j>=0; --j){
        cout << setw(8) << rvals[j] << ", " << cvals[j];
        cout << setw(8) << horizontalval[j] << setw(18) << anagramval[j] << endl;
    }
}
//using input from a file and outputting to file
void outfile(char* file1, char* file2)
{   
    string inword;
    vector<string> words={" "};
    vector<string> anagramval, horizontalval;
    vector<int> rvals, cvals;
    //gets file for the input
    ifstream ifs(file1);
    ifs >> inword; //takes word in as string variable "inword"
    Board crossboard;
    if (!ifs){ //checks that input file exists
        cout << "Error opening file " << file1 << endl;
        return;
    }
    while (!ifs.eof()){ //go through the file
        if (inword!="."){ //until there is a period
            if (inword.length() <= 15){ //makes sure the word is less than or equal to 15 characters
                for (int i=0; i<inword.length(); i++){
                    inword[i]=toupper(inword[i]);//makes the current character upper case (ends up making all the words all uppercase
                }
                auto it = words.begin();
                while (it !=words.end() && inword.length() < it->length())
                    ++it;
                words.insert(it, inword);//add the current word to the vector of strings "words" which is storing all the words
                anagramval.push_back(crossboard.anagram(inword));//add the current word to the vector of strings that stores all the words to later have their letters shuffled to use as clues
            }
            else
                cout << "One of the words in your file is too long." << endl; 
                //returns appropriate error if word in file is too long
        }
        ifs >> inword;//takes the next word and repeats
    }
    crossboard.placeFirst(words[0]);//uses placeFirst method to place the first word
    rvals.push_back(crossboard.getRow());//records the position of the letter of the first word
    cvals.push_back(crossboard.getCol());
    horizontalval.push_back("Across");//records the orientation of the first word (which is always horizontal)

    auto it = words.begin();//goes through all the words 
    advance(it, 1);
    for (it; it!=words.end(); ++it){
        crossboard.placeNext(*it);//uses placeNext method to place all the other words
        rvals.push_back(crossboard.getRow());//records the position of the first letter of each word in a vector
        cvals.push_back(crossboard.getCol());
        if (crossboard.getHA()==true)//records the orientation of each word to add to the clues later
            horizontalval.push_back("Down");
        else 
            horizontalval.push_back("Across");
    }
    ofstream ofs;//outputs output to a new file named by the user
    ofs.open(file2);
    crossboard.printout(ofs);//uses the prinout method to output the output
    ofs << "Clues: " << endl; //prints out the clues
    ofs << endl;
    int size =cvals.size();
    for (int j = size-2; j >= 0; --j){
        ofs << setw(8) << rvals[j] << ", " << cvals[j];
        ofs << setw(8) << horizontalval[j] << setw(18) << anagramval[j] << endl;
    }
}
