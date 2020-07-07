// Recursive function to generate the Sierpinski triangle fractal.
// From main, you would call this function to draw the outer triangle.
// The function will then recurse to draw all the inner triangles
// (you will of course have to write a triangle drawing function).
// NOTE:
// you may only use this code if you fully understand how it works.

#include "gfx.h"
#include <stdlib.h> 
#include <cmath>
#include <iostream>
using namespace std;
//void tree(int,int, int, int, int);
void tree(int, int, int, float);
int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=20;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "tree");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            tree(w/2, h-marg, (h/3), -pi/2);
            //tree(w/2, h-marg, w/2, 3*h/5, (h-marg)-(3*h/5));

    }


    return 0;
}



//void tree( int x1, int y1, int x2, int y2, int len)
void tree(int x1, int y1, int len, float ang)
{
    float pi=atan(1)*4; //calculate pi
   // Base case. 
    if( abs(len) < 15 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
    gfx_line(x1, y1, x1+len*cos(ang), y1+len*sin(ang));
   
    //len=pow((pow(y2-y1, 2)+pow((x2-x1), 2)), (1/2))/2;
    //cout << x1 << ' ' << x2;
  // gfx_line(x1, y1, x1+x1*cos(2*pi/5), y1+y1*sin(2*pi/5));
   //gfx_line(x3, y3, x1, y1);

   // Recursive calls
    //tree(x2, y2, x2-x2*sin(2*pi/5), y2-y2*sin(2*pi/5), len);
    //tree(x2, y2, x2-x2*cos(4*pi/5), y2-y2*sin(4*pi/5), len);
   tree(x1+len*cos(ang), y1+len*sin(ang), 2*len/3, ang+pi/6);
   tree(x1+len*cos(ang), y1+len*sin(ang), 2*len/3, ang-pi/6);
   //tree(x1, y1, );
   //tree(x1, y1, );
}

