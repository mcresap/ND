//Maria Cresap
//CSE20311
//lab 4 - ndfootball.cpp
/*uses a file with Notre Dame's football record and lets the user choose what stats they want to be displayed. The user can either choose to see the record for a given year, the years with a minumum number of losses or wins, or years with either a winning or losing season.*/
#include <iostream>
#include "nd_data.h"
using namespace std;
/*name functions to be created and what types of variables will need to be called from the main function*/
void record(int);
void nlosses(int, int);
void nwins(int, int);
void swin(int);
void sloss(int);
int main(){
    //ask user what they want to do/see
    int choice=0, year=0, l=0, size=0, w=0;    
    cout << "1: display the record for a given year." << endl;
    cout << "2: display years with at least n losses." << endl;
    cout << "3: display years with at least n wins." << endl;
    cout << "4: display years with a losing record." << endl;
    cout << "5: display years with a winning record." << endl;
    cout << "6: exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    //verify user input
    while (choice >6 || choice <1){
         cout << "Invalid choice." << endl;
         cout << "1: display the record for a given year." << endl;
         cout << "2: display years with at least n losses." << endl;
         cout << "3: display years with at least n wins." << endl;
         cout << "4: display years with a losing record." << endl;
         cout << "5: display years with a winning record." << endl;
         cout << "6: exit" << endl;
         cout << "Enter your choice: ";
         cin >> choice;
    }
    /*call appropriate function depending on the user's input and stop asking the user to choose after they choose to exit (6)*/
    while (choice!=6){
        //record for a given year
        if (choice==1){
            size = sizeof(losses)/sizeof(losses[0]);
            //call function for the record of a given year
            record(size);
            //reprompt user
            cout << "1: display the record for a given year." << endl;
            cout << "2: display years with at least n losses." << endl;
            cout << "3: display years with at least n wins." << endl;
            cout << "4: display years with a losing record." << endl;
            cout << "5: display years with a winning record." << endl;
            cout << "6: exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            //verify user input
            while (choice >6 || choice <1){
                cout << "Invalid choice." << endl;
                cout << "1: display the record for a given year." << endl;
                cout << "2: display years with at least n losses." << endl;
                cout << "3: display years with at least n wins." << endl;
                cout << "4: display years with a losing record." << endl;
                cout << "5: display years with a winning record." << endl;
                cout << "6: exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
        } 
        //years with at least n losses
        else if (choice==2){
            /*calculate the size of the losses array because it will change as the years go on*/
            size = sizeof(losses)/sizeof(losses[0]);
            cout << "Enter the minimum number of losses: " << endl;
            //take user input into the variable l
            cin >> l;
            /*call number of losses function using the user's input and the size of the losses array in the function*/
            nlosses(l, size);
            //reprompt the user 
            cout << "1: display the record for a given year." << endl;
            cout << "2: display years with at least ""n"" losses." << endl;
            cout << "3: display years with at least ""n"" wins." << endl;
            cout << "4: display years with a losing record." << endl;
            cout << "5: display years with a winning record." << endl;
            cout << "6: exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            //verify user input
            while (choice >6 || choice <1){
                cout << "Invalid choice." << endl;
                cout << "1: display the record for a given year." << endl;
                cout << "2: display years with at least ""n"" losses." << endl;
                cout << "3: display years with at least ""n"" wins." << endl;
                cout << "4: display years with a losing record." << endl;
                cout << "5: display years with a winning record." << endl;
                cout << "6: exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }  
        }
        //years with at least n wins
        else if (choice==3){
            /*calculate the size of the wins array because it will change when more years are added to it*/
            size = sizeof(wins)/sizeof(wins[0]);
            cout << "Enter the minimum number of wins: " << endl;
            //assign user input value to the variable w
            cin >> w;
            /*call number of wins function using size and user inputted w from the main function in this function*/ 
            nwins(w, size);
            //reprompt the user
            cout << "1: display the record for a given year." << endl;
            cout << "2: display years with at least ""n"" losses." << endl;
            cout << "3: display years with at least ""n"" wins." << endl;
            cout << "4: display years with a losing record." << endl;
            cout << "5: display years with a winning record." << endl;
            cout << "6: exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            //verify user input
            while (choice >6 || choice <1){
                cout << "Invalid choice." << endl;
                cout << "1: display the record for a given year." << endl;
                cout << "2: display years with at least ""n"" losses." << endl;
                cout << "3: display years with at least ""n"" wins." << endl;
                cout << "4: display years with a losing record." << endl;
                cout << "5: display years with a winning record." << endl;
                cout << "6: exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
        }
        //years with losing records
        else if (choice==4){
            /*calculate size of the losses array because it will change as years are added*/
            size = sizeof(losses)/sizeof(losses[0]);
            //call season loss function using size value from main function
            sloss(size);
            //reprompt user
            cout << "1: display the record for a given year." << endl;
            cout << "2: display years with at least ""n"" losses." << endl;
            cout << "3: display years with at least ""n"" wins." << endl;
            cout << "4: display years with a losing record." << endl;
            cout << "5: display years with a winning record." << endl;
            cout << "6: exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            //verify user input
            while (choice >6 || choice <1){
                cout << "Invalid choice." << endl;
                cout << "1: display the record for a given year." << endl;
                cout << "2: display years with at least ""n"" losses." << endl;
                cout << "3: display years with at least ""n"" wins." << endl;
                cout << "4: display years with a losing record." << endl;
                cout << "5: display years with a winning record." << endl;
                cout << "6: exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
        }      
        //years with winning records
        else if (choice==5){ 
            /*calculate size of the losses array because it is the same size as the wins array and it will change over the years*/
            size = sizeof(losses)/sizeof(losses[0]);
            //call season wins function
            swin(size);
            //reprompt user
            cout << "1: display the record for a given year." << endl;
            cout << "2: display years with at least ""n"" losses." << endl;
            cout << "3: display years with at least ""n"" wins." << endl;
            cout << "4: display years with a losing record." << endl;
            cout << "5: display years with a winning record." << endl;
            cout << "6: exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            //verify user input
            while (choice >6 || choice <1){
                cout << "Invalid choice." << endl;
                cout << "1: display the record for a given year." << endl;
                cout << "2: display years with at least ""n"" losses." << endl;
                cout << "3: display years with at least ""n"" wins." << endl;
                cout << "4: display years with a losing record." << endl;
                cout << "5: display years with a winning record." << endl;
                cout << "6: exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            }
        }
   }
   cout << "Thank you!" << endl;

return 0;
}
void record(int size){
    int year=0;
    //prompt user for input of the desired year's record and store value in variable year
    cout << "Enter the year: " << endl;
    cin >> year;
        //verify user input of the year and reprompt user if it is invalid
        while (year>(size+1900) || year<1900){
              cout << "Invalid year. Enter the year: " << endl;
              cin >> year;
        }
    /*display the record fot the chosen year subtract 1900 from the year value because the user enters a year and the function chooses the value that starts at 0 not 1900*/
    cout << "Wins: " << wins[year-1900] << endl;
    cout << "Losses: " << losses[year-1900] << endl;
}
/*use variable l that is the user's chosen number of losses and variable for size of the array in this functio*/
void nlosses(int l, int size){
    int  n, year, i=0;
    cout << "Years with at least " << l << " losses: ";
    /*loop through the entire array and set n to the current value of the array on each loop*/
    while (i<=size){
        n=losses[i];
        /*display the year when the number of losses of the current element of the array is larger than the user's inputted desired minimum*/
        if (n>=l){
            year=i+1900;
            cout << year << " ";
        }
        i++;
    }
    cout << "\n";
}
/*use variable w that is the user's chose number of wins and the variable size in this function*/
void nwins(int w, int size){
    int s, i=0, year;
    cout << "Years with at least " << w << " wins: ";
    /*loop through the entire array and set s to the current value of the array on each loop*/
    while (i<=size){
        s=wins[i];
        /*display the year when the number of wins of the current element of the array is larger than the user's inputted desired minimum*/
        if (s>=w){
            year =i+1900;
            cout << year << " ";
        }
        i++;
    }
    cout << "\n";
}
//uses variable for size of the losses array from the main function in this function
void swin(int size){
    int win, loss, i=0;
    cout << "Years with a winning record: ";
    /*loops through all years and sets the value of the current element of each array (wins and losses) to a variable win and loss respectively on each loop*/
    while (i<=size){
        win=wins[i];
        loss=losses[i];
        //displays the year when it was a winning season
        if (win>loss){
            cout << i+1900 << " ";
        }
        i++;
    }
    cout << "\n";
}
void sloss(int size){
    int win, loss, i=0;
    cout << "Years with a losing record: ";
    /*loops through all the years in the array and sets the value of the current element of each array (wins and losses) to a variable win and loss respectively on each loop*/
    while (i<=size){
        loss=losses[i];
        win=wins[i];
        //displays the year if it was a losing season
        if (loss>win){
            cout << i+1900 << " ";
        }
        i++;
    }
    cout << "\n";
}
