// Recursive function to generate the Sierpinski triangle fractal.
// From main, you would call this function to draw the outer triangle.
// The function will then recurse to draw all the inner triangles
// (you will of course have to write a triangle drawing function).
// NOTE:
// you may only use this code if you fully understand how it works.

#include "gfx.h"
#include <stdlib.h> 
//#include <cmath>
void square(int, int, int, int, int, int, int, int);

int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=170;

    gfx_open(w, h, "sierpinski");
    gfx_color(255, 255, 255);
    while (c!='q'){
        c=gfx_wait();
        if (c==1)
            square(marg, marg, w-marg, marg, marg, h-marg, w-marg , h-marg);
    }
    return 0;
}



void square( int x1, int y1, int x2, int y2, int x3, int y3 , int x4, int y4)
{
   // Base case. 
   if( abs(x2-x1) < 3 ) return;

   // Draw the triangle
   //mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );
   gfx_line(x1, y1, x2, y2);
   gfx_line(x2, y2, x4, y4);
   gfx_line(x4, y4, x3, y3);
   gfx_line(x3, y3, x1, y1);

   // Recursive calls
  /* square( x1-(x2-x1)/4, y1-(y3-y1)/4, x1+(x2-x1)/4, y1-(y3-y1)/4, x1-(x2-x1)/4, y1+(y3-y1)/4, x1+(x2-x1)/4, y1+(y3-y1)/4);
   square( x2-(x2-x1)/4, y2-(y3-y1)/4, x2+(x2-x1)/4, y2-(y3-y1)/4, x2-(x2-x1)/4, y2+(y3-y1)/4, x2+(x2-x1)/4, y2+(y3-y1)/4);
   square( x3-(x2-x1)/4, y3-(y3-y1)/4, x3+(x2-x1)/4, y3-(y3-y1)/4, x3-(x2-x1)/4, y3+(y3-y1)/4, x3+(x2-x1)/4, y3+(y3-y1)/4);
   square( x4-(x2-x1)/4, y4-(y3-y1)/4, x4+(x2-x1)/4, y4-(y3-y1)/4, x4-(x2-x1)/4, y4+(y3-y1)/4, x4+(x2-x1)/4, y4+(y3-y1)/4);*/
   square( x1-(x2-x1)/5, y1-(y3-y1)/5, x1+(x2-x1)/5, y1-(y3-y1)/5, x1-(x2-x1)/5, y1+(y3-y1)/5, x1+(x2-x1)/5, y1+(y3-y1)/5);
   square( x2-(x2-x1)/5, y2-(y3-y1)/5, x2+(x2-x1)/5, y2-(y3-y1)/5, x2-(x2-x1)/5, y2+(y3-y1)/5, x2+(x2-x1)/5, y2+(y3-y1)/5);
   square( x3-(x2-x1)/5, y3-(y3-y1)/5, x3+(x2-x1)/5, y3-(y3-y1)/5, x3-(x2-x1)/5, y3+(y3-y1)/5, x3+(x2-x1)/5, y3+(y3-y1)/5);
   square( x4-(x2-x1)/5, y4-(y3-y1)/5, x4+(x2-x1)/5, y4-(y3-y1)/5, x4-(x2-x1)/5, y4+(y3-y1)/5, x4+(x2-x1)/5, y4+(y3-y1)/5);
}

