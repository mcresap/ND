//Maria Cresap
//lifeboard.h
//CSE 20311 Lab 8
//interface for Lifeboard class
class Lifeboard {
    public:
        //constructor
        Lifeboard();
        ~Lifeboard();//deconstructor
        int getRow();
        int getCol();
        bool getPos(int, int);//get space
        void setPos(int, int, bool);//set space
        void setSpacePos(int, int);
        void setSpaceNeg(int, int);
        void advance();//next iteration
        int checkNearby(int, int);//gets the surrounding cells
        void display();
    private:
        int Row;
        int Col;
        bool board[40][40]; //makes 2D array of spaces
};
