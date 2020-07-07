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
void square(int, int, int, int, double);

int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=100;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "square spiral");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            square(w-marg, h-marg, 100, 500, pi/4);
    }
    return 0;
}



void square( int x1, int y1, int r, int r2, double theta1) //r2 radius of big circle, r radius of square
{
    float pi=atan(1)*4; //calculate pi
   // Base case. 
    if( abs(r2) < 10 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   //for (int i=0; i<5; i++){
    double theta=pi/4;
    gfx_line(x1+r*cos(theta), y1+r*sin(theta),x1-r*cos(theta), y1+r*sin(theta) );
    gfx_line(x1-r*cos(theta), y1+r*sin(theta),x1-r*cos(theta), y1-r*sin(theta) );
    gfx_line(x1-r*cos(theta), y1-r*sin(theta),x1+r*cos(theta), y1-r*sin(theta) );
    gfx_line(x1+r*cos(theta), y1-r*sin(theta),x1+r*cos(theta), y1+r*sin(theta) );
    //gfx_line(x1-r, y1+r, x1-r, y1-r);
    //gfx_line(x1-r, y1-r, x1+r, y1-r);
    //gfx_line(x1+r, y1-r, x1+r, y1+r);

   // Recursive calls
    square(800*.5+.8*r2*cos(theta1+2*pi/11), 800*.5+.8*r2*sin(theta1+2*pi/11), 9*r/10, 9*r2/10, theta1+2*pi/11);

   //}
  // sno(x1, y1, x1-x1*cos(2*pi/5), y1-y1*sin(2*pi/5));
   //sno(x1, y1, x1);
   //sno(x1, y1, );
   //sno(x1, y1, );
}

