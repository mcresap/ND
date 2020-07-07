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
void spiral(int, int, float, float);

int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=100;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "spiral of spirals");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            spiral(w/2, h/2, 550, pi/5);
    }
    return 0;
}



void spiral( int x1, int y1, float r,  float x) //r2 radius of big circle, r radius of square
{
    float pi=atan(1)*4; //calculate pi
    int  a, b;
   // Base case. 
    if( r < 1 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   /*for (int i=0; i<max; i++){
       x=i*.1;
       a=((x1+2*i)*cos(x));
       b=((y1+2*i)*sin(x));
       gfx_point(a, b);
   }*/
    a=x1+r*cos(x);
    b=y1+r*sin(x);
    gfx_point(a, b);//spiral going clockwise
    /*for (int i=0; i<max; i++){
        gfx_point(x1, y1);
        spiral(400+.8*r2*cos(x+2*pi/11), 400+.8*r2*sin(x+2*pi/11), 9*r/10, 9*r2/10, x+2*pi/11);
    }*/

   // Recursive calls
    spiral(x1, y1, 0.9*r, x+pi/5);
    spiral(a, b, 0.33*r, x+pi/5);
    //spiral(x1+.99*r2*cos(x+2*pi/11), y1+.99*r2*sin(x+2*pi/11), .1*r, .99*r2, x+2*pi/11);
    //for (int i=0; i<max; i++){
    //gfx_point(x1, y1);
    //spiral(x1+.8*r2*cos(x+2*pi/11), y1+.8*r2*sin(x+2*pi/11), 9*r/10, 9*r2/10, x+2*pi/11);
   // }
    //gfx_point(spiral(400+.8*r2*cos(x+2*pi/11), 400+.8*r2*sin(x+2*pi/11), 9*r/10, 9*r2/10, x+2*pi/11), spiral(400+.8*r2*cos(x+2*pi/11), 400+.8*r2*sin(x+2*pi/11), 9*r/10, 9*r2/10, x+2*pi/11));
    //spiral(x1*.99, y1*.99, );

   
}

