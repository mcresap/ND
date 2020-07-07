#include   <iostream>
using   namespace   std;
void   func1(int   *,   int); 
void   func2(char   *); 
void   show1(int   *,   int); 
void   show2(char   *);
int   main()
{
    int   a[]   =   {6,   7,   9},   *p1   =   a;
                
    char   s[]   =   "CSCPEG",   *p2   =   s;
        func1(p1,   3);     
        show1(p1,   3);     
        func2(p2);
        show2(p2);
    return   0;
}
void   func1(int   *p,   int   n) 
{
     for(int   i=0;   i<n;   i++)
      {   
              (*p)++;   p++;   } 
}
void   func2(char   *p) {
      while(*p)
           {   (*p)++;   p++;   } }
void   show1(int   *p,   int   n) {
      for(int   i=0;   i<n;   i++)
           cout   <<   *p++   <<   endl; }
void   show2(char   *p) {
      while(*p)
            cout   <<   *p++   <<   endl; }
