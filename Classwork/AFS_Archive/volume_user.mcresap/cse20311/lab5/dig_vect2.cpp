//Maria Cresap
//CSE 10320 Lab 5 dig_vect2.cpp
/*This program finds the frequency of occurence of digits in an array containing random digits using vectors and the <vector> class and iterators.*/
#include <iostream>
using namespace std;
//include the vector class
#include <vector>
//made freq and digits vectors to be used in the findfreq and results functions introduced here
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

    return 0;
}
//passes freq by reference because this function needs to change the freq vector
void findfreq(vector<int> digits, vector<int> &freq)
{
    //loops through every digit 0-9
    for (int i=0; i<10; i++){
        //checks every element in digits vector using iteration
        for (auto it=digits.begin(); it<digits.end();it++){
            /*if current element in digits vector has the same value as the current digit then it adds to the current freq value which tracks the frequency */
            if (*it==i){
                freq[i]++;
            }
        }
    }
}
//displays the results of the frequency of each digit
void results(vector<int> digits, vector<int> freq)
{
   //loops through the freq vector with iteration to display the frequency of each digit
   for (auto it=freq.begin(); it<freq.end();it++){
       cout <<  "digit " << it-freq.begin() << " occurs " << *it << " times" << endl;
   }
}
