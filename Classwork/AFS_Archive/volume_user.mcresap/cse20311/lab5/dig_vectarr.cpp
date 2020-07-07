//Maria Cresap
//CSE 10320 Lab 5 dig_vectarr.cpp
/*This program find the frequency of digits in an array containing random digits using vectors and arrays and the <vector> and <array> classes. This program also uses both iterating and indexing. */
#include <iostream>
using namespace std;
//include vector and array classes
#include <vector>
#include <array>
//findfreq will pass digits vector by value and freq array by reference
void findfreq(vector<int> digits, array<int, 10> &freq);
//results function will pass digits vector and freq array by value
void results(vector<int> digits, array<int, 10> freq);
int main(){
    //make digits a vector because it can potentially be more dynamic
    vector<int> digits ={4,3,6,5,7,8,9,4,6,3,1,3,5,7,6,3,6,
                         5,6,7,0,2,9,7,1,3,2,1,6,7,4,6,2,8,
                         1,4,5,6,0,2,7,6,4,5,6,8,3,5,7,1,5};
    //make freq an array of 10 zeros because it is static and we are only checking digits 0-9
    array<int, 10> freq = {0};

    findfreq(digits, freq); // compute digits' frequencies
    results(digits, freq);  // display frequencies for each digit

    return 0;
}

void findfreq(vector<int> digits, array<int, 10> &freq)
{
    //loops through every digit 0-9
    for (int i=0; i<10; i++){
        //used iteration to check every element in the digits vector
        for (auto it=digits.begin(); it<digits.end();it++){
            /*checks if current element in digits vector has the same value as the current digit being checked in the outer loop and if the values are the same then increments the freq vector value of the current element*/
            if (*it==i){
                freq[i]++;
            }
        }
    }
}
     
void results(vector<int> digits, array<int, 10> freq)
{
   //displays the frequency of each digit 0-9 using indexing 
   for (int n=0; n<=9; n++){
       cout <<  "digit " << n << " occurs " << freq[n] << " times" << endl;
   }
}
