//Maria Cresap
//CSE 20311 - lab 5 - mysayings.cpp
/*program uses a file of common phrases and displays a menu of options for the user to do things with the phrases or display different phrases.*/
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
//introduces finctions to be made after the main function
void show(vector<string>);
void enter(vector<string> &);
void list(vector<string>);
void newfile(vector<string>);
int main(){

    int choice=0;
    string s, quote, substr;
    cout << "Welcome to the sayings manager!" << endl;
    cout << "Enter the name of startup file: " << endl;
    cin >> s;
    /*takes user's inputted file to use and opens it to stream as "myfile"*/
    ifstream myfile;
    myfile.open(s);
    if (!myfile){ //checks if the file exists
        cout << "Error in opening file " << s << endl;
        return 0;
    }
    //takes the input of the file and stores it in a vector of strings called "file"
    vector<string> file;
    //uses the myfile stream to set quote to be the first line of the file
    getline(myfile, quote);
    /*loops through the file and puts each line of the file after the next, stored in the string "quote". Uses get line to know when to break for each new line being put in quote and uses push_back to put it at the end of the new list.*/
    while (!myfile.eof()){
        file.push_back (quote);
        getline(myfile, quote);
    }
    //prompts the user for an option from the menu until the user quits
    while (choice!=5){
        cout << "Tasks to perform:" << endl;
        cout << "1: show all sayings. \n2: enter a new saying." << endl;
        cout << "3: list sayings that contain a given substring." << endl;
        cout << "4: save all sayings in a new file." << endl;
        cout << "5: quit." << "\nEnter your choice: " << endl;
        cin >> choice;
        //checks to make sure the user's choice is valid int he range of option numbers
        if (choice>5 || choice<1){
            cout << "Invalid choice!" << endl;
            cout << "Tasks to perform:" << endl;
            cout << "1: show all sayings. \n2: enter a new saying." << endl;
            cout << "3: list sayings that contain a given word." << endl;
            cout << "4: save all sayings in a new file." << endl;
            cout << "5: quit." << "\nEnter your choice: " << endl;
        }
        /*takes the user's choice and calls the corresponding function to perform the selected task*/
        if (choice==5)
            break; /*ends the program and stops asking for a choice when the user selects 5 to quit*/
        if (choice==1)
            show(file);
        if (choice==2)
            enter(file);
        if (choice==3)
            list(file);
        if (choice==4)
            newfile(file);
    }
    return 0;
}
/*function to list all the sayings in the file. Takes the vector of strings "file" which has all the sayings*/
void show(vector<string> file){
    //uses iteration to display the file's contents
    for (auto it=file.begin(); it < file.end(); it++)
        cout << *it << endl;
    cout << endl;
}
/*function to let the user enter a new saying. Passes the vector of strings containing what was in the file by reference so the vector can be changed (added to)*/
void enter(vector<string> &file){
    cout << "Enter a new saying: ";
    //takes the user's inputted saying and stores it as a line that is a string
    string newsay;
    cin.ignore();
    getline(cin, newsay);
    /*uses push_back to add the user's saying to the end of the vector of strings of the contents of the file "file"*/
    file.push_back (newsay);
}
//function that lists sayings that contain a given substring the user enters
void list(vector<string> file){
    int n=0;
    cout << "Enter the search word: ";
    //takes the user's inputted substring and stores in as a string line
    string substr;
    cin.ignore();
    getline (cin, substr);
    /*loops through the entire vector of strings that is the contents of the file, line by line*/
    for (int i=0; i<file.size(); i++){
        //displays the lines that contain the given substring somewhere in them
        if (file[i].find(substr) != string:: npos){
            cout << file[i] << endl;
            //set n to 1 so that the program doesn't display that there was no match
            n=1;
        }
    }
    /*if no match to the substring is found, n remains 0 and the program tells the user there was no match*/
    if (n==0)
        cout << "There are no matches." << endl;
}
//function that saves all the current sayings to a file
void newfile(vector<string> file){
    string r;
    cout << "Enter the name of the file where all sayings will be saved: ";
    cin >> r;
    /*outputs the contents of the old file and any added sayings to a new file with name chosen by the user*/
    ofstream myfileo (r);
    //outputs each line of the file into this new file, one by one in this for loop
    for (int i=0; i<file.size();i++)
        myfileo << file[i] << endl;
}
