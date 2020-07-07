#include <iostream>
using namespace std;

void findfreq(int digits[], int freq[], int size);
void results(int digits[], int freq[], int size);

int main()
{
    // array with random digits
    int digits[] = {4,3,6,5,7,8,9,4,6,3,1,3,5,7,6,3,6,
                    5,6,7,0,2,9,7,1,3,2,1,6,7,4,6,2,8,
                    1,4,5,6,0,2,7,6,4,5,6,8,3,5,7,1,5};
    int freq[10] = {0};    // array to tally the frequency of digits
    int size = sizeof(digits)/sizeof(int);   // find the array's size

    findfreq(digits, freq, size); // compute digits' frequencies
    results(digits, freq, size);  // display frequencies for each digit
      
    return 0;
}

void findfreq(int a[], int freq[], int sz)
{
    int c=0;
    for (int i=0; i<10; i++){
           for (int j=0;j<sz;j++){
               if (i==a[j]){
                   c++;
                   freq[i]=c;
               }
           }
           c=0;
    }
    //only need 1 loop
    //for (int i=0; i< sz; i++)
    //freq[a[i]]++;
}
void results(int a[], int freq[], int sz)
{
    for (int n = 0; n <= 9; n++) 
    cout <<  "digit " << n << " occurs " << freq[n] << " times" << endl;
}
