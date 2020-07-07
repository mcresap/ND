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
void sno(int, int, int);

int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=20;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "snowflake");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            sno(w/2, h/2, (h/2)- h-marg);

    }


    return 0;
}



void sno( int x1, int y1, int r)
{
    float pi=atan(1)*4; //calculate pi
   // Base case. 
    if( abs(r) < 10 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   for (int i=0; i<5; i++){
    gfx_line(x1, y1, x1+r*cos(i*2*pi/5+pi/2), y1+r*sin(i*2*pi/5+pi/2));
    //cout << x1 << ' ' << x2;
  // gfx_line(x1, y1, x1+x1*cos(2*pi/5), y1+y1*sin(2*pi/5));
   //gfx_line(x3, y3, x1, y1);

   // Recursive calls
    sno(x1+r*cos(i*2*pi/5+pi/2), y1+r*sin(i*2*pi/5+pi/2), r/3);
   }
  // sno(x1, y1, x1-x1*cos(2*pi/5), y1-y1*sin(2*pi/5));
   //sno(x1, y1, x1);
   //sno(x1, y1, );
   //sno(x1, y1, );
}

