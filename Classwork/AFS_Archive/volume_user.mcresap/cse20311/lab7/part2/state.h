//Maria Cresap
//interface for the State class
//state.h
//CSE 20311 lab 7 part 2
#include <string>
using namespace std;
class State {
    public:
        //constructors
        State();
        State(string, string, string, int, int, int);
        //destructor
        ~State();
        //access methods
        string getAbbrev();
        string getName();
        string getCapital();
        int getPop();
        int getYear();
        int getReps();
        void setAbbrev(string);
        void setName(string);
        void setCapital(string);
        void setPop(int);
        void setYear(int);
        void setReps(int);
        string getLower();//makes the state name lowercase
        //utility methods
        void print();//prints a certain state's information
        bool popOver(int);//checks if the population of a state is over a certain number
        bool yearOver(int);//checks if the year founded of a state is over a certain number
        double ratios();//calculates the ratio of the # reps to the population of a state
    private:
        string abbreviation;
        string name;
        string capital;
        int population;
        int year;
        int reps;
};
