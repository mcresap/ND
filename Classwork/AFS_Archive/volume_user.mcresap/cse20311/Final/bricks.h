//bricks.h
//interface for the bricks class
#include "gfxnew.h"
class Bricks {
    public:
        Bricks(); //constructor
        ~Bricks();//deconstructor;
        int getX();
        int getY();
        //void setX(int);
        void setPos(int, int);
        void setPosDead(int, int);
        void setPosLive(int, int);
    private:
        int X;
        int Y;
};
