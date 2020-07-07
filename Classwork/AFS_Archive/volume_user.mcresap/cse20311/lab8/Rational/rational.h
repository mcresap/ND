//Maria Cresap
// rational.h
// interface for the Rational class
class Rational { 
    //to overload input and output operators
    friend ostream& operator<<(ostream&, Rational&);
    friend istream& operator>>(istream &, Rational &);
  public:
    //constructore
    Rational();
    Rational(int, int);
    //destructor
    ~Rational();
    //access methods
    int getNumer();
    int getDenom();
    void setNumer(int);
    void setDenom(int);
    void setRat(int, int);
    //utility methods
    //overloading arithmetic operators
    Rational operator+(Rational);
    Rational operator-(Rational);
    Rational operator*(Rational);
    Rational operator/(Rational);
    //making signs of fractions look better
    void sign();
    //simplifying fractions
    void simplify();
  private:
    int numer;
    int denom;
};

