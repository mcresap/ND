#include <iostream>
using namespace std; 
#define SIZE 5
void disp(int[], int); 
int ok(int[], int); 
void fn(int[], int);

int main() 
{
    int i, a[SIZE];
    for (i = 0; i < SIZE; i++) 
        a[i] = i*i+1;
    disp(a, SIZE);
    cout << ok(a, SIZE) << endl; fn(a, SIZE);
    disp(a, SIZE);
    fn(a, SIZE);
    disp(a, SIZE);
return 0;
}

void disp(int a[], int s) {
    int i;
    for (i = 0; i < s; i++)
        cout << a[i] << " "; cout << endl;
     }

int ok(int a[], int s) 
        {
        int i, m = 0; 
        for (i = 0; i<s;i++)
            m += a[i];
        return m;
}

      
void fn(int a[], int s) {
    int i, z = a[0];
    for (i = 0; i < s-1; i++)
        a[i] = a[i+1]; 
    a[s-1] = z;
}
