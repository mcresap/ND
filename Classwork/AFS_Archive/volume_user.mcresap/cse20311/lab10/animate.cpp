//Maria Cresap
//CSE 20311 Lab 10
//animate.cpp
//animation of a ferris wheel 
#include "gfx.h"
#include <unistd.h>
#include <cmath>
int main()
{
    char c=0; //defines event
    int w=700; //window width
    int h=700; //window height
    int r=20; //radius to draw squares/huts
    int pause=200000;
    float pi=atan(1)*4; //calculate pi
    float cx=350, cy=350; //center point of the ferris wheel
    float radi=200;
    float x3, y3; //point to draw line to from the center
    float dtheta=pi/4; //separation of spokes
    float v=0; 
    float dt=0.025;

    gfx_open(w, h, "Ferris Wheel"); //open window for drawing
    gfx_color(0, 230, 200); //set color to blue-green

    while(c!='q'){
        gfx_clear();
        gfx_color(24, 158, 55); //set color to green for grass
        gfx_line(0, 600, w, 600); //draw line for ground/grass
        gfx_color(0, 102, 204); //set color to blue for base
        gfx_line(cx-25, 599, cx, cy);//draw triangle-like base
        gfx_line(cx+25, 599, cx, cy);
        gfx_color(255, 255, 153); // set color to yellow for center wheel thing
        gfx_circle(cx, cy, 12); //draw two center circles
        gfx_circle(cx, cy, 20);
        for(int i=0; i<8; i++){ //make 8 spokes
           gfx_color(24, 158, 131); //set color to blue-green for spokes
           x3=cx+radi*cos(dtheta*i+v); //separate lines/spokes but changing point line is drawn to
           y3=cy+radi*sin(dtheta*i+v);
           gfx_line(cx,cy,x3,y3); //draw spoke
           gfx_color(153, 153, 0); //color yellow-green for boxes
           gfx_line(x3+r, y3+r, x3-r, y3+r); //make square for hut for people in ferris wheel to sit in
           gfx_line(x3-r, y3+r, x3-r, y3-r);
           gfx_line(x3-r, y3-r, x3+r, y3-r);
           gfx_line(x3+r, y3-r, x3+r, y3+r);
        }
        gfx_flush();
        v=v+dt; //make the spokes spin
        usleep(pause);
        if (gfx_event_waiting()){ //pause and figure out event only if an event happens
            c=gfx_wait(); //wait for an event and return what event was
            switch (c){
                case 'x': //press x to stop the ferris wheel
                    dt=0;
                    break;
                case 'f': //press f to speed up the ferris wheel
                    dt+=0.05;
                    break;
                case 's': //press s to slow down the ferris wheel
                    dt-=0.05;
                    break;
            }
        }
    }
    return 0;
}
