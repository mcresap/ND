// Recursive function to generate the Sierpinski triangle fractal.
// From main, you would call this function to draw the outer triangle.
// The function will then recurse to draw all the inner triangles
// (you will of course have to write a triangle drawing function).
// NOTE:
// you may only use this code if you fully understand how it works.

#include "gfx.h"
#include <stdlib.h> 
//#include <cmath>
void sierpinski(int, int, int, int, int, int);

int main() {
    int w=700;
    int h=700;
    char c=0;
    int marg=20;

    gfx_open(w, h, "sierpinski");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            sierpinski(marg, marg, w-marg, marg, w/2, h-marg);

    }


    return 0;
}



void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
   // Base case. 
   if( abs(x2-x1) < 5 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   gfx_line(x1, y1, x2, y2);
   gfx_line(x2, y2, x3, y3);
   gfx_line(x3, y3, x1, y1);

   // Recursive calls
   sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
   sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
   sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

