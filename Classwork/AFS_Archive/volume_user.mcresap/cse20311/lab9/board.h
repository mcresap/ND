//Maria Cresap
//board.h
//CSE 20311 Lab 9 
//interface for crossword board
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Board {
    public:
        Board();
        ~Board();
        int getRow();
        int getCol();
        bool getHA();
        void print();
        string anagram(string);
        ostream& printout(ostream &);
        void placeFirst(string);
        void placeNext(string);
        bool isValid(int, int, int, string);
        bool isVectorHoriz(int, int);
    private:
        int Row;
        int Col;
        bool horizacross;
        char board[15][15];
};
