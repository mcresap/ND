//statemain.cpp
//Maria Cresap
//CSE 20311 Lab 7 Part 2
//main function for State, reads data from csv file and stores it in a vector and prompts the user with a menu for getting information from the data
#include <iostream>
using namespace std;
#include <fstream>
#include <vector>
#include <iomanip>
#include "state.h"
//all functions to be made (all streams passed by reference)
void display(vector<State> &);
void popover(vector<State> &);
void yearover(vector<State> &);
void ratiostate(vector<State> &);
void statein(vector<State> &);

int main()
{
    int choice=0;
    ifstream ifs;
    string abbreviation, name, capital, yr_s, pop_s, reps_s;
    int yr, pop, reps;
    //opens the usstates.csv file
    ifs.open ("usstates.csv");
    //creates a vector for the State class called states
    vector<State> states;
    //sta is a member of State
    State sta;
    //goes through the entire file and adds each word or number as a line/unit together but each state's information list is one line
    //uses commas to seperate each unit (units being name, abbreviation, capital, year, reps, and population)
    //peek looks ahead to the next character to check to make sure we don't include the EOF character
    while (ifs.peek()!=EOF){
        getline(ifs, abbreviation, ',');
        getline(ifs, name, ',');
        getline(ifs, capital, ',');
        getline(ifs, pop_s, ',');
        getline(ifs, yr_s, ',');
        getline(ifs, reps_s, '\n');
        //turns the string of pop_s into an integer pop
        pop=stoi(pop_s);
        //turns the string yr_s into an integer yr
        yr=stoi(yr_s);
        //turns the string reps_s into an integer reps
        reps=stoi(reps_s);
        //all the string variables in State
        sta=State(abbreviation, name, capital, pop, yr, reps);
        //puts each new line after the previous
        states.push_back(sta);
    }
    //displays the menu of options to the user until they choose the exit option (6)
    while (choice!=6){ 
        cout << "\nTasks to perform:\n 1: Display all data\n 2: Check if population of a state is over a certain number\n 3: Check if a state was founded after an entered date\n 4: Calculate the ratio of number of representatives to population of an entered state\n 5: Information of an entered state\n 6: Quit\n";
        cin >> choice;
        //checks that the user inputs a choice within the range of choices and gives and error and reprompts if they don't
        if (choice>6 || choice<1)
            cout << "Invalid choice!" << endl;
        //exits when the user chooses the quit option and ends program
        if (choice==6)
            break;
        if (choice==1)
            display(states);
        if (choice==2)
            popover(states);
        if(choice==3)
            yearover(states);
        if (choice==4)
            ratiostate(states);
        if (choice==5)
            statein(states);
    }
    return 0;
}

//function that displays all the information of all the states
void display(vector<State> &s)
{
    //iterates through all of the file's contents
    for (auto it=s.begin(); it!=s.end(); ++it){
        //uses the get methods for each piece of information to list the info of a state
        cout << it->getAbbrev() << ", ";
        cout << it->getName() << ", ";
        cout << it->getCapital() << ", ";
        cout << it->getPop() << ", ";
        cout << it->getYear() << ", ";
        cout << it->getReps() << endl;
    }
}
//function that lists the states with population over the entered number
void popover(vector<State> &s)
{
    int x;
    bool found;
    cout << "Enter the minimum population value you want to check: " <<  endl;
    cin >> x;
    cout << "States with population over " << x << ": " << endl;
    //iterates through all of the file's contents
    for (auto it=s.begin(); it<s.end(); it++){
        //uses popOver method to list the states with population over the entered number because popOver returns true if the population is over the entered value
        if (it->popOver(x)){
            cout << it->getName() << endl;
            //uses the bool "found" to check that there was at least one state that had a population over the entered number
            found=true;
        }
    }
    //tells the user no states were found if none have population over the entered number
    if (!found)
        cout << "No states had population over the entered number." << endl;
}
//function that lists all states founded after an entered year
void yearover(vector<State> &s)
{
    int y;
    bool found;
    cout << "Enter the minimum year you want to check: " <<  endl;
    cin >> y;
    //checks that the entered year is positive and exits the function if it is not
    if (y>0){
        cout << "States founded after year " << y << ": " << endl;
        //iterated through the entire file
        for (auto it=s.begin(); it<s.end(); it++){
            //uses yearOver methos to list the states founded after the entered year with yearOver returning true if the state was founded after the inputted year
            if (it->yearOver(y)){
                cout << it->getName() << endl;
                //uses found to check that there was at least one state founded after the entered year
                found=true;
            }
        }
        //tells the user no states were found if none were founded after their year
        if (!found)
            cout << "No states founded after the entered year." << endl;
        }
    //gives an error message if the user enteres a negative value for the year
    else if (y<0)
        cout << "Invalid year." << endl;
}
//function that calculates the ratio of the # of reps to the population of a state
void ratiostate(vector<State> &s)
{
    string stateu, d;
    bool found;
    cout << "Enter the state you want to find the ratio of representatives to population: " << endl;
    cin.ignore();
    //keeps the user's inputted string state name as one unit/line
    getline(cin, stateu);
    cout << "The ratio of representatives to population is: " << endl;
    //indexes through the users inputted state name and makes it all lowercase
    for (int i=0; i<stateu.length(); i++)
        stateu[i]=tolower(stateu[i]);
    //iterates through the entire file
    for (auto it=s.begin();it<s.end();it++){
        //uses the getLower method to make the state name in the file lowercase and checks if it's the same as the user'sinputted state because both will then be all lowercase
        if (it->getLower()==stateu){
            //uses the ratios method to find the ration of reps to pop with 10 decimal places
            cout << setprecision(10) << fixed << it->ratios();
            //uses found to check that the inputted state is a valid one
            found=true;
        }
    }
    //if the inputted state is not a valid one, gives the user an error 
    if (!found)
        cout << "The state you entered was invalid." << endl;
}
//function that lists all the information of a chosen state
void statein(vector<State> &s)
{
    string stateu;
    bool found;
    cout << "Enter the state you want the information of: " << endl;
    cin.ignore();
    getline(cin, stateu);
    //indexes through the users inputted state name and makes it all lowercase
    for (int i=0; i<stateu.length(); i++)
        stateu[i]=tolower(stateu[i]);
    //iterates through the entire file's contents
    for (auto it=s.begin(); it<s.end(); it++){
        //uses the getLower methos to make the state name lowercase and compares it to the user's inputted state name and if they are the same, prints that state's info
        if (it->getLower()==stateu){
            //uses the print method to print the state's information
            it->print();
            //uses found to check that the state inputted by the user was valid
            found=true;
        }
    }
    //returns an error message if the inputted state was invalid
    if (!found)
        cout << "The state you entered was invalid." << endl;
}
