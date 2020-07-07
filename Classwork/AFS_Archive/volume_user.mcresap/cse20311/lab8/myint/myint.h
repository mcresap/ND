// myint.h
class MyInt {
  public:
    MyInt();
    MyInt(int);
    ~MyInt();
    int getValue();
    void setValue(int);
    void display();
    // prototypes for operator+ and operator- go here:
    MyInt operator+(MyInt);
    MyInt operator-(MyInt);
  private:
    int value;
};

