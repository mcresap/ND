// testfont.cpp
// this program showcases how to use the font functions to identify
//  a font's geometry, and, as an example, displays around a string
//  a rectangle that is scaled to the string's size (length and height)

#include "gfxnew.h"

int main()
{
  int wid = 800, ht = 500; 
  char c;

//  char thefont[] = "-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso8859-1";
  // or, try this font to see the scaling:
  char thefont[] = "12x24";

  char mytext[] = "Notre Dame Fighting Irish";

  int x_winctr, y_winctr;            // window's center
  int pxl_w, pxl_h, x_txt, y_txt;    // text string's parameters
  int x_r, y_r, rect_wid, rect_ht;   // rectangle's parameters
  int pad = 10;                      // padding for the rectangle

  gfx_open(wid, ht, "My window"); 
  gfx_clear();
  gfx_color(255,255,255); 
  gfx_changefont(thefont);

  while(true) { 
    // find the window's center point coordinates
    x_winctr = gfx_windowwidth()/2;
    y_winctr = gfx_windowheight()/2;

    // determine the text string's width and height in pixels
    pxl_w = gfx_textpixelwidth(mytext, thefont);
    pxl_h = gfx_textpixelheight(mytext, thefont);

    // display the text, dead center, by first determining its lower left corner
    x_txt = x_winctr - pxl_w/2;
    y_txt = y_winctr + pxl_h/2;
    gfx_text(x_txt, y_txt, mytext);

    // draw a rectangle around the text, dead center, with a given padding
    // first determine its top left corner's x,y coordinates
    x_r = x_txt - pad; 
    y_r = y_txt - pxl_h - pad;
    // now compute its width and height
    rect_wid = pxl_w + 2*pad;
    rect_ht = pxl_h + 2*pad; 
    // now draw the rectangle with the above four values
    gfx_rectangle(x_r, y_r, rect_wid, rect_ht);

    gfx_flush();

    if (gfx_wait() == 'q') break;
  }

  return 0;
}

