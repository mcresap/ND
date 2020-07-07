//board.cpp
//Maria Cresap
//CSE 20311 Lab 9
//implementation
#include <iostream>
#include <algorithm>
#include <fstream>
#include "board.h"
using namespace std;

//constructor
Board::Board()
{
    for (int col=0; col<15; col++){
        for (int row=0; row<15; row++){
            board[col][row]=' ';//sets a 2D array ofspaces
        }
    }
}
//destructor
Board::~Board()
{ }

int Board::getRow()
{ return Row+1; }//so coordinates of beginnings of words start from 1

int Board::getCol()
{ return Col+1; }//so coordinates of beginnings of words start from 1

bool Board::getHA()
{ return horizacross; }
//prints the solution and empty puzzle 
void Board::print()
{
    cout << "Solution: " << endl;
    cout << endl;

    for (int col=0; col<15; col++){
        for (int row=0; row<15; row++){
            if (board[col][row] == ' ')
                cout << '.';
            else 
                cout << board[col][row];//if there is not a blank space in the current spot, print the letter that belongs in that spot
        }
        cout << endl;
    }
    cout << "Crossword Puzzle: " << endl;
    cout << endl;
    for (int col=0; col<15; col++){
        for (int row=0; row<15; row++){
            if (board[col][row] == ' ')//if there is not a letter in the current spot, prints #
                cout << "#";
            else 
                cout << " ";//if there is a letter in the current space, prints a space to show you need to fill it in
        }
        cout << endl;
    }
}
//prints output to file instead of in command line/window 
ostream& Board::printout(ostream &file)
{
    file << "Solution: " << endl;
    file << endl;
    //prints output the same way as in the "print" method
    for (int col=0; col<15; col++){
        for (int row=0; row<15; row++){
            if (board[col][row] == ' ')
                file << '.';
            else 
                file << board[col][row];
        }
        file << endl;
    }
    file << "Crossword Puzzle: " << endl;
    file << endl;
    for (int col=0; col<15; col++){
        for (int row=0; row<15; row++){
            if (board[col][row] == ' ')
                file << "#";
            else 
                file << " ";
        }
        file << endl;
    }
    return file;
}
//shuffles the letters of a word to provide the hint
string Board::anagram(string inword)
{
    //rearranges the letters of the words alphabetically
    sort(inword.begin(), inword.end());
    int max = rand() % (inword.length() -1) +1; //generates a random number of times to swap the letters
    for (int i=0; i < max; i++){//swaps letters
        char temp=inword[i];
        inword[i]=inword[i+1];
        inword[i+1]=temp;
    }
    return inword;//returns the shuffled word/letters
}
//places the longest word in the middle of the board
void Board::placeFirst(string inword)
{
    int size=inword.size();
    int dist=(15-size)/2;
    int i=0;
    for (int position=dist; position<(size+dist); position++){
        board[7][position]=inword[i];
        i++;
    }
    Col=dist;
    Row=7;
}
//places all the words after the first word
void Board::placeNext(string similar)
{
    bool okay=false;
    bool work=false;//to check if a word is ever placed
    bool direction;
    int r, c;
    int size=similar.size();
    char letpos;
    for (int i=0; i<size; ++i){
        for (int y=0; y<15; y++){
            for (int x=0; x<15; x++){
                if (similar[i]==board[y][x]){//if a letter in the word you're trying to add matched a letter already on the board, prepares to print the new word 
                    r=y;
                    c=x;
                    letpos=i;
                    okay=isValid(letpos, r, c, similar);
                    work=true;//word was placed if program enters this if statement
                }
                if (okay){
                    break;
                }
            }
            if (okay){
                break;
            }
        }
        if (okay) {
            break;
        }
        if (work == false){
            break;
            //prevents a seg fault because r and c would have garbage values if the program never enters the if statement commented on above
        }
    }
    if (work==false){//if a word is never placed on the board, returns an error with which word couldn't be placed
        cout << "Error! This word could not be placed: " << similar << endl;
        return;
    }
    bool yes= isVectorHoriz(c, r);
    if (okay) { //place the word in the board
        int size1=similar.size();
        int right=(size1-(letpos+1));
        int left=(size1-(right+1));
        if (isVectorHoriz(c, r)){ //if word is vertical
            for (int i=1; i<=right; i++){
                board[r+i][c]=similar[letpos+i];
            }
            for (int j=-1; j>= -left; j--){
                board[r+j][c]=similar[letpos+j];
            }
            Row=r-left;
            Col=c;
            horizacross=true;
        }
        else { //if word is horizontal
            for (int k=1; k<=right; k++){
                board[r][c+k]=similar[letpos+k];
            }
            for (int l=-1; l>=-left; l--){
                board[r][c+l]=similar[letpos+l];
            }
            Row=r;
            Col=c-left;
            horizacross=false;
        }
    }
}
//checks how to place the word and if it is possible to place it
bool Board::isValid(int letpos, int r, int c, string word)
{
    bool okay1=false, okay2=false, okay3=false;
    int size=word.size();
    int right=(size - (letpos+1));
    int left=(size - (right+1));
    int count1=0, count2=0;
    if (isVectorHoriz(c, r)) { //place word vertically
        for (int i=1; i<=right; i++){
            if ((board[i+r][c-1] == ' ') && (board[r+i][c+1]== ' ')) {
                count1++;
            }
        }
        for (int j=-1; j>=-left; j--) {
             if ((board[j+r][c-1] == ' ') && (board[r+j][c+1]== ' ')) {
                count2++;
             }
        }
        if ((board[r+right+1][c] == ' ') && (board[r-left-1][c] == ' ')) {
            okay3=true;
        }
        if ((right+r)>14) {
            okay3=false;
        }
        if ((-left+r)<0) {
            okay3=false;
        }
    }
    else { //place word horizontally
        for (int i=1; i<=right; i++) {
            if ((board[r-1][c+i] == ' ') && (board[r+1][c+i] == ' ')) {
                count1++;
            }
        }
        for (int j=-1; j>= -left; j--) {
            if ((board[r-1][c+j] == ' ') && (board[r+1][c+j] == ' ')) {
                count2++;
            }
        }
        if ((board[r][c+right +1] == ' ') && (board[r][c-left-1] == ' ')) {
            okay3=true;
        }
        if ((right + c)>14) {
            okay3=false;
        }
        if ((-left + c) < 0) {
            okay3=false;
        }
    }
    if ((count1==right) && (count2==left)) {
        okay2=true;
    }
    if (okay2 && okay3) {
        okay1=true;
    }
    return okay1;
}
//checks if there are words around where you're trying to add a word 
//and then determines how you should place the next word
bool Board::isVectorHoriz(int c, int r)
{
    if (((r+1)>15 || (board[r+1][c] == ' ')) && ((r-1)<0 || (board[r-1][c] == ' '))) { //string is horiz
        return true; //build vertically
    }      
    else { //string is vertical
        return false; //build horizontally
    }
}
