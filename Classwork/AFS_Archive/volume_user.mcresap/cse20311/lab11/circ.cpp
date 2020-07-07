// Recursive function to generate the Sierpinski triangle fractal.
// From main, you would call this function to draw the outer triangle.
// The function will then recurse to draw all the inner triangles
// (you will of course have to write a triangle drawing function).
// NOTE:
// you may only use this code if you fully understand how it works.

#include "gfx.h"
#include <stdlib.h> 
#include <cmath>
void circ(int, int, int);

int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=290;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "circles");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            circ(w/2, h/2, marg);

    }


    return 0;
}



void circ( int x1, int y1, int r)
{
    float pi=atan(1)*4; //calculate pi
   // Base case. 
   if( abs(r) < 1 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   gfx_circle(x1, y1, r);
   //gfx_line(x2, y2, x3, y3);
   //gfx_line(x3, y3, x1, y1);

   // Recursive calls
   circ( x1+r, y1, r*pi/10);
   circ(x1+r*cos(pi/3), y1+r*sin(pi/3), r*pi/10);
   circ(x1-r*cos(pi/3), y1+r*sin(pi/3), r*pi/10);
   circ(x1+r*cos(pi/3),y1-r*sin(pi/3), r*pi/10);
   circ(x1-r*cos(pi/3), y1-r*sin(pi/3), r*pi/10);
   circ(x1-r, y1, r*pi/10);
}

