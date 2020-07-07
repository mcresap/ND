#include "gfxnew.h"
#include <vector>
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void drawBrick(int x, int y);

int main()
{
    bool began=false;
    bool won;
    // initialize variables for window
    int w=1000, h=700, pxl_w, pxl_h, x_txt, y_txt;
    int edge = 200;
    int lives=0;
    char c;
    char thefont[]="12x24";
    char newfont[]="7x14";
    char mytext[]="BRICK BREAKER :)";
    // initialize variables for bricks
    vector<int> brickX;
    vector<int> brickY;
    vector<bool> brickBool;
    int brickw=100;
    int brickh=40;
    // initialize variables for ball
    int r=10;
    srand(time(NULL));
    int dx=rand() % 16 - 8;
    int dy=rand() % 9;
    if (abs(dx)<3 || abs(dy)<3){
        dx=4;
        dy=4;
    }
    int ballx=w/2, bally=h-r-20;
    bool bounced=false;
    // initialize variables for paddle
    int padw=100, padh=20;
    int padx=w/2-padw/2, pady=h-padh;
    // create window
    gfx_open(w+edge, h, "Brick Breaker");
    gfx_color(255, 255, 255);
    gfx_changefont(thefont);
    pxl_w=gfx_textpixelwidth(mytext, thefont);//determine the text string's width and height in pixels
    pxl_h=gfx_textpixelheight(mytext, thefont);
    //display the text dead center by first determining its lower left center
    x_txt=(w+edge)/2-pxl_w/2;
    y_txt=h/2-pxl_h/2;
    gfx_text(x_txt, y_txt, mytext);
    gfx_changefont(newfont);
    gfx_text(x_txt, y_txt+50, "Press SPACE to release the ball");
    gfx_text(x_txt, y_txt+75, "Use the right and left arrow keys to move the paddle");
    gfx_text(x_txt, y_txt+100, "Press 'q' to quit");
    gfx_text(x_txt, y_txt+125, "Left click with the mouse to begin!");

    // create vector of brick center points and if they are alive or dead
    for (int i=0; i<10; i++){
        brickX.push_back(brickw*i+brickw/2);
        brickY.push_back(brickh/2);
        brickBool.push_back(true);
    }
    for (int i=0; i<10; i++){
        brickX.push_back(brickw*i+brickw/2);
        brickY.push_back(brickh+brickh/2);
        brickBool.push_back(true);
    }
    for (int i=0; i<10; i++){
        brickX.push_back(100*i+50);
        brickY.push_back(2*brickh+brickh/2);
        brickBool.push_back(true);
    }

    // enter while loop until user quits the game
    while (c!='q'){
        c=gfx_wait();
        if (c==1){ //click to start
            gfx_clear();
            lives=3;
        }

        // enter while loop once user has clicked to begin game
        while (lives>0){
            // randomly determine initial velocity
            srand(time(NULL));
            int dx=rand() % 16 - 8;
            int dy=rand() % 9;
            if (abs(dx)<3 || abs(dy)<3){
                dx=4;
                dy=4;
            }
            // print lives on side of board
            gfx_line(w, 0, w, h);
            drawBrick(w+100, 200);
            gfx_changefont(newfont);
            gfx_text(w+82, 201, "LIVES");
            for (int i=0; i<lives; i++){
                gfx_color(175, 33, 78);
                gfx_fill_circle(w+82+(i*17), 210, 5);
            }
            gfx_color(255, 255, 255);
            // draw the bricks
            for (int i=0; i!=brickX.size(); i++){
                if (brickBool[i]==true){
                    drawBrick(brickX[i], brickY[i]);
                }
            }
            // draw ball
            gfx_circle(ballx, bally, r);
            // draw paddle
            gfx_fill_rectangle(padx, pady, padw, padh);
            gfx_flush();
            c=gfx_wait();
            // allow user to change starting position of ball and paddle
            if (c=='Q'){ //left arrow key
                if (padx>0){
                    gfx_color(0, 0, 0);
                    gfx_circle(ballx, bally, r);
                    gfx_fill_rectangle(padx, pady, padw, padh);
                    padx-=10;
                    ballx-=10;
                    gfx_color(255, 255, 255);
                    gfx_circle(ballx, bally, r);
                    gfx_fill_rectangle(padx, pady, padw, padh);
                }
            }
            if (c=='S'){ //right arrow key
                if (padx+padw<w){
                    gfx_color(0, 0, 0);
                    gfx_fill_rectangle(padx, pady, padw, padh);
                    gfx_circle(ballx, bally, r);
                    padx+=10;
                    ballx+=10;
                    gfx_color(255, 255, 255);
                    gfx_circle(ballx, bally, r);
                    gfx_fill_rectangle(padx, pady, padw, padh);
                }
            }
            if (c==32) //space bar clicked to start
                began=true;
            if (c=='q'){ //if user clicks q, quit program
                lives=0;
                break;
            }

            // enter while loop once ball has been released from paddle
            while (began==true){
                // draw the current bricks
                for (int i=0; i!=brickX.size(); i++){
                    if (brickBool[i]==true){
                        drawBrick(brickX[i], brickY[i]);
                    }
                    else{
                        //cout << "DEAD AT: " << brickX[i] << " " << brickY[i] << endl;
                    }
                }
                // draw paddle
                gfx_fill_rectangle(padx, pady, padw, padh);
                gfx_flush();
                if (gfx_event_waiting()){
                    c=gfx_wait();
                }
                // allow user to move paddle to left and right
                if (c=='Q'){ //left arrow key
                    if (padx>0){
                        gfx_color(0, 0, 0);
                        gfx_fill_rectangle(padx, pady, padw, padh);
                        padx-=10;
                        gfx_color(255, 255, 255);
                        gfx_fill_rectangle(padx, pady, padw, padh);
                    }
                }
                if (c=='S'){ //right arrow key
                    if (padx+padw<w){
                        gfx_color(0, 0, 0);
                        gfx_fill_rectangle(padx, pady, padw, padh);
                        padx+=10;
                        gfx_color(255, 255, 255);
                        gfx_fill_rectangle(padx, pady, padw, padh);
                    }
                }
                //move the ball if it's inside the bounds of the game
                if (ballx+dx+r < w || ballx+dx+r>0){
                    gfx_color(0, 0, 0);
                    gfx_circle(ballx, bally, r);
                    ballx=ballx-dx;
                    bally=bally-dy;
                    gfx_color(255, 255, 255);
                    gfx_circle(ballx, bally, r);
                }
                // run checks for ball hitting left and right walls
                if (ballx+r+abs(dx) >= w || ballx-r-abs(dx) <= 0)
                    dx=-dx;
                // run checks for ball bottom of bricks
                for (int i=0; i!=brickX.size(); i++){
                    // checks if brick is still alive
                    if (brickBool[i]==true){
                        if (bally-r-abs(dy) <= brickY[i]+brickh/2 && bally-r-abs(dy) >= brickY[i]-brickh/2){
                            if (ballx >= brickX[i]-brickw/2 && ballx <= brickX[i]+brickw/2){
                                // make hit brick black
                                gfx_color(0, 0, 0);
                                drawBrick(brickX[i], brickY[i]);
                                // change brickBool position to false to say it is dead
                                brickBool[i]=false;
                                // print lives on side of board
                                gfx_color(255, 255, 255);
                                gfx_line(w, 0, w, h);
                                drawBrick(w+100, 200);
                                gfx_changefont(newfont);
                                gfx_text(w+82, 201, "LIVES");
                                for (int i=0; i<lives; i++){
                                    gfx_color(175, 33, 78);
                                    gfx_fill_circle(w+82+(i*17), 210, 5);
                                }
                                gfx_color(0, 0, 0);
                                dy=-dy;
                                gfx_circle(ballx, bally, r);
                                bally = bally+5;
                            }
                        }
                        // run check for ball hitting top of bricks
                        if (bally+r+abs(dy) >= brickY[i]-brickh/2 && bally+r+abs(dy) <= brickY[i]+brickh/2){
                            if (ballx >= brickX[i]-brickw/2 && ballx <= brickX[i]+brickw/2){
                                // make hit brick black
                                gfx_color(0, 0, 0);
                                drawBrick(brickX[i], brickY[i]);
                                // change brickBool position to false to say it is dead
                                brickBool[i]=false;
                                // print lives on side of board
                                gfx_color(255, 255, 255);
                                gfx_line(w, 0, w, h);
                                drawBrick(w+100, 200);
                                gfx_changefont(newfont);
                                gfx_text(w+82, 201, "LIVES");
                                for (int i=0; i<lives; i++){
                                    gfx_color(175, 33, 78);
                                    gfx_fill_circle(w+82+(i*17), 210, 5);
                                }
                                gfx_color(0, 0, 0);
                                dy=-dy;
                                gfx_circle(ballx, bally, r);
                                bally = bally-5;
                            }
                        }
                    }
                }
                // run checks for ball hitting brick sides
                for (int i=0; i!=brickX.size(); i++){
                    // checks if brick is still alive
                    if (brickBool[i]==true){
                        // checks hitting left side of ball
                        if (ballx-r-abs(dx) <= brickX[i]+brickw/2 && ballx-r-abs(dx) >= brickX[i]-brickw/2){
                            if (bally >= brickY[i]-brickh/2 && bally <= brickY[i]+brickh/2){
                                // make hit brick black
                                gfx_color(0, 0, 0);
                                drawBrick(brickX[i], brickY[i]);
                                // change brickBool to false to say it is dead
                                brickBool[i]=false;
                                // print lives on side of board
                                gfx_color(255, 255, 255);
                                gfx_line(w, 0, w, h);
                                drawBrick(w+100, 200);
                                gfx_changefont(newfont);
                                gfx_text(w+82, 201, "LIVES");
                                for (int i=0; i<lives; i++){
                                    gfx_color(175, 33, 78);
                                    gfx_fill_circle(w+82+(i*17), 210, 5);
                                }
                                gfx_color(0, 0, 0);
                                dx=-dx;
                                gfx_circle(ballx, bally, r);
                                ballx = ballx+5;
                            }
                        }
                        // checks hitting right side of ball
                        if (ballx+r+abs(dx) >= brickX[i]-brickw/2 && ballx+r+abs(dx) <= brickX[i]+brickw/2){
                            if (bally >= brickY[i]-brickh/2 && bally <= brickY[i]+brickh/2){
                                // make hit brick black
                                gfx_color(0, 0, 0);
                                drawBrick(brickX[i], brickY[i]);
                                // change brickBool to false to say it is dead
                                brickBool[i]=false;
                                for (int i=0; i<lives; i++){
                                    gfx_color(175, 33, 78);
                                    gfx_fill_circle(w+82+(i*17), 210, 5);
                                }
                                gfx_color(0, 0, 0);
                                dx=-dx;
                                gfx_circle(ballx, bally, r);
                                ballx = ballx-5;
                            }
                        }
                    }
                }
                
                // check for ball bouncing off of paddle
                if (bally+r >= pady){
                    if (ballx >= padx && ballx <= padx+padw){
                        dy=-dy;
                    }
                }
                // check for ball hitting bottom of screen
                if (bally+r >= h){
                    gfx_color(0, 0, 0);
                    gfx_circle(ballx, bally, r);
                    gfx_fill_rectangle(padx, pady, padw, padh);
                    gfx_color(255, 255, 255);
                    // subtract one life, and exit current while loop
                    lives=lives-1;
                    began=false;
                    // reset variables so ball and paddle will be in middle
                    ballx = w/2;
                    bally = h-padh-r;
                    padx = w/2-padw/2;
                    dx = abs(dx);
                    dy = abs(dy);
                    gfx_clear();
                    srand(time(NULL));
                    int dx=rand() % 16 - 8;
                    int dy=rand() % 9;
                    if (abs(dx)<3 || abs(dy)<3){
                        dx=4;
                        dy=4;
                    }
                }
                // check for ball hitting top of screen
                if (bally-r <=0)
                    dy=-dy;
                // if user clicks q, quit the program
                if (c=='q'){
                    lives=0;
                    began=false;
                    break;
                }

                // reset c to an unused value so that it won't continously do the previously clicked function
                c='X';

                // check if the game has been won
                for (int i=0; i!=brickX.size(); i++){
                    if (brickBool[i]==true){
                        won = false;
                    }
                }

                // if user won game, go to winner screen
                while (won == true){
                    gfx_changefont(thefont);
                    gfx_text(x_txt, y_txt, "You Won!");
                    gfx_text(x_txt, y_txt+50, "Click to play again");
                    gfx_text(x_txt, y_txt+100, "Press 'q' to quit");
                    c=gfx_wait();
                    if (c==1){
                        lives=-1;
                        began=false;
                        gfx_clear();
                        won = false;
                        for (int i=0; i!=brickX.size(); i++){
                            brickBool[i]=true;
                        }
                    }
                    if (c=='q'){ //q to quit
                        lives=0;
                        began=false;
                        break;
                    }
                }

                    
                // if user loses all lives, go to loser screen
                while (lives==0){
                    gfx_clear();
                    gfx_changefont(thefont);
                    gfx_text(x_txt, y_txt, "You Lost!");
                    gfx_text(x_txt, y_txt+50, "Click to play again");
                    gfx_text(x_txt, y_txt+100, "Press 'q' to quit");
                    c=gfx_wait();
                    if (c==1){ //replay and get lives back
                        lives=-1;
                        began=false;
                        gfx_clear();
                        for (int i=0; i!=brickX.size(); i++){
                            brickBool[i]=true;
                        }
                    }
                    if (c=='q'){ //q to quit
                        lives=0;
                        began=false;
                        break;
                    }
                }
                won = true;
            }
        }
    }
    return 0;
}

// draw bricks function
void drawBrick(int x, int y){
    int w=50, h=20;
    //gfx_color(255, 255, 255); 
    gfx_line(x-w, y-h, x+w, y-h);
    gfx_line(x+w, y-h, x+w, y+h);
    gfx_line(x+w, y+h, x-w, y+h);
    gfx_line(x-w, y+h, x-w, y-h);
}
