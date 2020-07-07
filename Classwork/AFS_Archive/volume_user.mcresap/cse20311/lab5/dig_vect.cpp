//Maria Cresap
//CSE 10320 Lab 5 dig_vect.cpp
/*This program finds the frequency of digits in an array containing random digits using vectors and the <vector> class and indexing. */
#include <iostream>

using namespace std;
//include vector class
#include <vector>
//made freq and digits to vectors which are used in the findfreq and results functions
void findfreq(vector<int> digits, vector<int> &freq);
void results(vector<int> digits, vector<int> freq);
int main(){
    //make digits and freq vectors
    vector<int> digits ={4,3,6,5,7,8,9,4,6,3,1,3,5,7,6,3,6,
                         5,6,7,0,2,9,7,1,3,2,1,6,7,4,6,2,8,
                              1,4,5,6,0,2,7,6,4,5,6,8,3,5,7,1,5};
    vector<int> freq (10, 0); //creates the freq vector made up of 10 zeros

    findfreq(digits, freq); // compute digits' frequencies
    results(digits, freq);  // display frequencies for each digit
i
    return 0;
}
//passes freq by reference because this function needs to change the freq vector
void findfreq(vector<int> digits, vector<int> &freq)
{
    //loops through every digit 0-9
    for (int i=0; i<10; i++){
        //check every element in the digits vector
        for (int j=0; j<digits.size(); j++)
            /*see if the current element in the digits vector has the same value as the current digit being checked*/
            if (digits[j]==i){
                /*if the values are the same then increment the freq vector in the current digit element number*/
                freq[i]++;
            }
    }
}
//displays results of the frequency of each digit
void results(vector<int> digits, vector<int> freq)
{
   //list every digit and the value it holds in the freq vector/the number of times it occurs
   for (int n = 0; n <= 9; n++) 
       cout <<  "digit " << n << " occurs " << freq[n] << " times" << endl;
}
