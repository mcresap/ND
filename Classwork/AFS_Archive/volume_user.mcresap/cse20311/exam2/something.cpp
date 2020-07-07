#include   <iostream>
using   namespace   std;
void   setup(int   &,   int   &,   int   &); 
int   something   (int,   int   &,   int   *); 
void   show(int,   int,   int,   int);
int   main()
    {
    int   x   =   0,   y   =   0,   z   =   0,   s   =   0;                 
       setup(x,   y,   z);
       s   =   something(x,   y,   &z);     
       show(x,   y,   z,   s);                               
       setup(x,   y,   z);
                                          
       s   =   something(y, z, &x);     
       show(x,   y,   z,   s);
                                            
       return   0;
    }
                                            
void   setup(int   &a,   int   &b,   int   &c) {
    a   =   1;   b   =   4;   c   =   7;
}
                                            
int   something   (int   a,   int   &b,   int   *c) {
                                                  
    a   +=   3;                                         
    b   =   2   +   *c;
    *c   +=   4;      
    return   a;
}                                  
void   show(int   a,   int   b,   int   c,   int   d)
{
    cout   <<   a   <<   ","   <<   b   <<   ","   <<   c   <<   ","   <<   d   <<   endl;
}
