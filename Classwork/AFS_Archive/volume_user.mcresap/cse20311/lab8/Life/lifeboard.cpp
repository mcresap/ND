//lifeboard.cpp
//Maria Cresap
//CSE 20311 Lab 8
//implementation
#include <iostream>
#include "lifeboard.h"
#include<iomanip>
#include <cstdlib>
using namespace std;

//constructor
Lifeboard::Lifeboard()
{
    //sets board to 40x40 and all dead cells
    Row=40;
    Col=40;
    for (int i=0; i<Row; i++){
        for (int j=0; j<Col; j++){
            board[i][j]=false;
        }
    }
}
//destructor
Lifeboard::~Lifeboard()
{ }

int Lifeboard::getRow()
{ return Row; }

int Lifeboard::getCol()
{ return Col; }

bool Lifeboard::getPos(int r, int c)
{ return board[r][c]; }

void Lifeboard::setPos(int r, int c, bool sign)
{ board[r][c]=sign; }

void Lifeboard::setSpacePos(int r, int c)
{ board[r][c]=true; }

void Lifeboard::setSpaceNeg(int r, int c)
{ board[r][c]=false; }
//advances through the board to make the correct cells alive or dead
void Lifeboard::advance()
{
    Lifeboard tempboard=Lifeboard();
    for (int i=0; i<Row; i++){ //loops through rows
        for (int j=0; j<Col; ++j){ //loops through columns
            tempboard.setPos(i, j, board[i][j]);
        }
    }
    for (int i=0; i<Row; i++){//loops through the rows
        for (int j=0; j<Col; j++){//loops through the columns

            if (tempboard.getPos(i,j) == false && tempboard.checkNearby(i,j)==3){ //if the cell is alive makes it true and they will then be marked alive with an X
                board[i][j]=true;
            }
            //if the cell is dead makes it dead/false
            else if (tempboard.getPos(i,j) == true && tempboard.checkNearby(i, j)!=3 && tempboard.checkNearby(i,j)!=2){ 
                board[i][j]=false;
            }
        }
    }
}
//checks surrounding cells of current cell
int Lifeboard::checkNearby(int r, int c)
{
    int count=0;
    for (int i=-1; i<=1; i++){ //loops through rows
        for (int j=-1; j<=1; j++){   //loops through columns
            if ((r+i)>=0 && (c+j)>=0 && (r+i)<Row && (c+j)<Col){
                if (board[r+i][c+j]==true){
                    count++;
                }
            }
        }
    }
    if (board[r][c]==true)
        count--; //loops counts the center cell so subtract 1 from count
    return count;
}
//displays the board
void Lifeboard::display()
{
    system("clear");//clears the page each iteration
    //displays the top boarder of the board
    for (int i=0; i<Col; i++){
        cout << "-";
    }
    cout << endl;
    //displays the side boarders of the board and fills in dead and live cells with X or space as appropriate
    for (int i=0; i<Row; i++){
        cout << "|";
        for (int j=0; j<Col; j++){
            if (board[i][j]==true){//marks live cells
                cout << "X";
            }
            else{
                cout << " ";
            }
        }
        cout << "|" << endl; //finishes the board with the last boarder piece
    }
    //displays the bottom boarder of the board
    for (int i=0; i<Col; i++)
        cout << "-";
    cout << endl;

}
