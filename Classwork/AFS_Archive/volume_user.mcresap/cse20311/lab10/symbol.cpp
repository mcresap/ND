//symbol.cpp
//Maria Cresap
//CSE 20311 Lab 10 - Symbolic Typewriter
//draws different shapes in different colors when different keys/clicks are used
#include "gfx.h"
#include <cmath>
int circle(int, int, int, float);
int poly(int, int, int, float);
int tri(int, int, int, float);
int sq(int, int, int, float);
int main()
{
    int w=500; //window width
    int h=400; //window height
    char c=0;
    bool exit=true;
    int x, y;
    float r=30;

    gfx_open(w, h, "My Window"); //open window for drawing

    while (exit){
        gfx_flush();
        c=gfx_wait(); //wait for user input/event
        x=gfx_xpos(); //get mouse click's x coordinate
        y=gfx_ypos(); //get mouse click's y coordinate
        switch(c){
            case 1: //click
                sq(c, x, y, r);
                break;
            case't':
                tri(c, x, y, r);
                break;
            case 'c':
                circle(c, x, y, r);
                break;
            case '3': //3 sided polygon
            case '4': //4 sided polygon
            case '5': //5 sided polygon
            case '6': //6 sided polygon
            case '7': //7 sided polygon
            case '8': //8 sided polygon 
            case '9': //9 sided polygon
                poly(c, x, y, r);
                break;
            case 27: //clear window with esc
                gfx_clear();
                break;
            case 'q': //quit if q is pressed
                exit=false;
        }
    }
    return 0;
}
//draw polygons with polar coordinates
int poly(int c, int x, int y, float r)
{
    c=c-48; //choice comes in as char so use ascii value to make it the correct int
    float pi=atan(1)*4; //calculate pi
    gfx_color(128, 0, 128); //change color to purple
    float dt=2*pi/c;
    float x1=0, x2=0, y1=0, y2=0;
    for (float t=0; t<c; t++){ 
        x1=x+r*cos(dt*t); //calculate the vertice locations
        y1=y+r*sin(dt*t);
        x2=x+r*cos(dt*(t+1)); //calculate the next vertex point
        y2=y+r*sin(dt*(t+1));
        gfx_line((int)x1, (int)y1, (int)x2, (int)y2); //make line from current to next vertex
    }
}
//draw circle
int circle(int c, int x, int y, float r)
{
    c=c-68;
    gfx_color(255, 255, 255); //changes color to white
    gfx_circle(x, y, r); //circle of radius 10
}
//draw triangle
int tri(int c, int x, int y, float r)
{
     gfx_color(0, 255, 0); //change color to green
     gfx_line(x-r, y+r, x+r, y+r);
     gfx_line(x+r, y+r, x, y-r);
     gfx_line(x, y-r, x-r, y+r);
}
//draw square
int sq(int c, int x, int y, float r)
{
     gfx_color(0, 0, 255); //change color to blue
     gfx_line(x+r, y+r, x-r, y+r);
     gfx_line(x-r, y+r, x-r, y-r);
     gfx_line(x-r, y-r, x+r, y-r);
     gfx_line(x+r, y-r, x+r, y+r);
}
