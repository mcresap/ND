//bounce.cpp
//Maria Cresap
//CSE 20311 Lab 10
//bouncing ball annimation
#include "gfx.h"
#include <unistd.h>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    int w=700; //window width
    int h=600; //window height
    char c=0;
    int r=20;
    int deltat=rand() % 5000 + 3000; //pause length 
    int dy1=rand() % 10 -5; //animation increment before click
    int dx1=rand() % 10 -5;
    if (dx1==0 || dy1==0){
        dx1=1;
        dy1=1;
    }
    int x1=rand() % w + 1; //x position before click
    int y1=rand() % h + 1; //y position before click

    gfx_open(w, h, "Bounce"); //open window for drawing
    gfx_color(0, 190, 255); //set the color to  blue

    while (c!='q'){ //continues until q is pressed
        gfx_clear(); //clears the screen
        gfx_circle(x1, y1, r); //draws the circle 
        gfx_flush();
        usleep(deltat); 
        if (((x1+dx1)<w || (x1+dx1)>0) && ((y1+dy1)>0 || (y1+dy1)<h)){ //move the circle if it is inside the bounds of the window
            x1=dx1+x1;
            y1=dy1+y1;
        }
        if ((x1<=r) || (x1>=w-r)) //reset the change in x if it hits a wall
            dx1=-dx1;
        if ((y1<=r) || (y1>=h-r))//reset the change in y if it hits a wall
            dy1=-dy1;
        if (gfx_event_waiting()){//pause and figure out event only if an event happens
            c=gfx_wait();//wair for an event and return what event was
            if (c==1){
                x1=gfx_xpos();//get the x position of the mouse click
                y1=gfx_ypos();//get the y position of the mouse click
                dx1=rand() % 10 -5; //change animation increment after click
                dy1=rand() % 10 -5; //change animation increment after click
                if (dx1==0 || dy1==0){
                    dx1=1;
                    dy1=1;
                }
            }
        }
    }
    return 0;
}

