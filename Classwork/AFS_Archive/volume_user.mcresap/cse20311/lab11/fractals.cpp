//Maria Cresap
//Lab 11 CSE 20311
//fractals.cpp
//draws different fractals based on what number the user presses
#include "gfx.h"
#include <stdlib.h> 
#include <cmath>
#include <iostream>
using namespace std;
void sierpinski(int, int, int, int,int ,int);
void shrink(int, int, int, int, int ,int ,int, int);
void square(int, int, int, int, double);
void circ(int, int, int);
void sno(int, int, int);
void tree(int,int, int, float);
void fern(int, int, int, float);
void spiral(int, int, float, float);
int main() {
    int w=800;
    int h=800;
    char c=0;
    int marg=20;
    int marg2=290;
    int marg3=100;
    int marg4=170;
    float pi=atan(1)*4; //calculate pi

    gfx_open(w, h, "Fractals"); //open window for drawing
    gfx_color(255, 255, 255); //make color white
    while (c!='q'){ //close window when q is pressed
        c=gfx_wait();//wait for an event and read it
        switch (c){
            case '1':
                gfx_clear();
                sierpinski(marg, marg, w-marg, marg, w/2, h-marg);
                break;
            case '2':
                gfx_clear();
                shrink(marg4, marg4, w-marg4, marg4, marg4, h-marg4, w-marg4, h-marg4);
                break;
            case '3':
                gfx_clear();
                square(w-marg3, h-marg3, marg3, 500, pi/4);
                break;
            case '4':
                gfx_clear();
                circ(w/2, h/2, marg2);
                break;
            case '5':
                gfx_clear();
                sno(w/2, h/2, h/3);
                break;
            case '6':
                gfx_clear();
                tree(w/2, h-marg, h/3, -pi/2);
                break;
            case '7':
                gfx_clear();
                fern(w/2, h-marg, (2*h/3), -pi/2);
                break;
            case '8':
                gfx_clear();
                spiral(w/2, h/2, 550, pi/5);
                break;
            default:
                gfx_clear();
                break;
        }
    }
    return 0;
}
//drawing the sierpinski triangle
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
    // Base case. 
    if( abs(x2-x1) < 5 ) return;
    // Draw the triangle
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x1, y1);
    // Recursive calls
    sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
    sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
    sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}
//drawing the shrinking squares
void shrink( int x1, int y1, int x2, int y2, int x3, int y3 , int x4, int y4)
{
    // Base case. 
    if( abs(x2-x1) < 3 ) return;
    // Draw the squares
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x4, y4);
    gfx_line(x4, y4, x3, y3);
    gfx_line(x3, y3, x1, y1);
    // Recursive calls
    shrink( x1-(x2-x1)/5, y1-(y3-y1)/5, x1+(x2-x1)/5, y1-(y3-y1)/5, x1-(x2-x1)/5, y1+(y3-y1)/5, x1+(x2-x1)/5, y1+(y3-y1)/5);
    shrink( x2-(x2-x1)/5, y2-(y3-y1)/5, x2+(x2-x1)/5, y2-(y3-y1)/5, x2-(x2-x1)/5, y2+(y3-y1)/5, x2+(x2-x1)/5, y2+(y3-y1)/5);
    shrink( x3-(x2-x1)/5, y3-(y3-y1)/5, x3+(x2-x1)/5, y3-(y3-y1)/5, x3-(x2-x1)/5, y3+(y3-y1)/5, x3+(x2-x1)/5, y3+(y3-y1)/5);
    shrink( x4-(x2-x1)/5, y4-(y3-y1)/5, x4+(x2-x1)/5, y4-(y3-y1)/5, x4-(x2-x1)/5, y4+(y3-y1)/5, x4+(x2-x1)/5, y4+(y3-y1)/5);
}
//drawing the spiral squares
void square( int x1, int y1, int r, int r2, double theta1) //r2 radius of big circle, r radius of square
{
    float pi=atan(1)*4; //calculate pi
    // Base case. 
    if( abs(r2) < 10 ) return;
    double theta=pi/4;
    //draw the square
    gfx_line(x1+r*cos(theta), y1+r*sin(theta),x1-r*cos(theta), y1+r*sin(theta) );
    gfx_line(x1-r*cos(theta), y1+r*sin(theta),x1-r*cos(theta), y1-r*sin(theta) );
    gfx_line(x1-r*cos(theta), y1-r*sin(theta),x1+r*cos(theta), y1-r*sin(theta) );
    gfx_line(x1+r*cos(theta), y1-r*sin(theta),x1+r*cos(theta), y1+r*sin(theta) );
    // Recursive calls
    square(800*.5+.8*r2*cos(theta1+2*pi/11), 800*.5+.8*r2*sin(theta1+2*pi/11), 9*r/10, 9*r2/10, theta1+2*pi/11);
}
//drawing the circular lace
void circ( int x1, int y1, int r)
{
    float pi=atan(1)*4; //calculate pi
    // Base case. 
    if( abs(r) < 1 ) return;
    //draw the circle
    gfx_circle(x1, y1, r);
    // Recursive calls
    circ( x1+r, y1, r*pi/10);
    circ(x1+r*cos(pi/3), y1+r*sin(pi/3), r*pi/10);
    circ(x1-r*cos(pi/3), y1+r*sin(pi/3), r*pi/10);
    circ(x1+r*cos(pi/3),y1-r*sin(pi/3), r*pi/10);
    circ(x1-r*cos(pi/3), y1-r*sin(pi/3), r*pi/10);
    circ(x1-r, y1, r*pi/10);
}
//drawing the snowflake
void sno( int x1, int y1, int r)
{
    float pi=atan(1)*4; //calculate pi
    //base case
    if( abs(r) < 1 ) return;
    //Draw the snowflake
    for (int i=0; i<5; i++){
        gfx_line(x1, y1, x1+r*cos(i*2*pi/5+pi/2), y1+r*sin(i*2*pi/5+pi/2));
        //Recursive call
        sno(x1+r*cos(i*2*pi/5+pi/2), y1+r*sin(i*2*pi/5+pi/2), r/3);
    }
}
//drawing the tree
void tree(int x1, int y1, int len, float ang)
{
    float pi=atan(1)*4; //calculate pi
    // Base case. 
    if( abs(len) < 2 ) return;
    // Draw the tree
    gfx_line(x1, y1, x1+len*cos(ang), y1+len*sin(ang));
    // Recursive calls
    tree(x1+len*cos(ang), y1+len*sin(ang), 2*len/3, ang+pi/6);
    tree(x1+len*cos(ang), y1+len*sin(ang), 2*len/3, ang-pi/6);
}
//drawing the fern
void fern(int x1, int y1, int len, float ang)
{
    float pi=atan(1)*4; //calculate pi
    // Base case. 
    if( abs(len) < 5 ) return;
    //draw the fern
    gfx_line(x1, y1, x1+len*cos(ang), y1+len*sin(ang));
    // Recursive calls
    fern(x1+len*cos(ang)*.25, y1+len*sin(ang)*.25, len/3, ang+pi/6);
    fern(x1+len*cos(ang)*.25, y1+len*sin(ang)*.25, len/3, ang-pi/6);
    fern(x1+len*cos(ang)*.5, y1+len*sin(ang)*.5, len/3, ang-pi/6 );
    fern(x1+len*cos(ang)*.5, y1+len*sin(ang)*.5, len/3, ang+pi/6);
    fern(x1+len*cos(ang)*.75, y1+len*sin(ang)*.75, len/3, ang+pi/6);
    fern(x1+len*cos(ang)*.75, y1+len*sin(ang)*.75, len/3, ang-pi/6);
    fern(x1+len*cos(ang), y1+len*sin(ang), len/3, ang+pi/6);
    fern(x1+len*cos(ang), y1+len*sin(ang), len/3, ang-pi/6);
}
//draw the spiral of spirals
void spiral( int x1, int y1, float r,  float x) //r2 radius of big circle, r radius of square
{
    float pi=atan(1)*4; //calculate pi
    int  a, b;
   // Base case. 
    if( r < 1 ) return;

    a=x1+r*cos(x);
    b=y1+r*sin(x);//spiral going clockwise
    gfx_point(a, b);//draw point
   // Recursive calls
    spiral(x1, y1, 0.9*r, x+pi/5);
    spiral(a, b, 0.33*r, x+pi/5);
}
