//Maria Cresap
// rational.h
// interface for the Rational class
class Rational {
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
    void print();
    //utility methods
    Rational add(Rational);
    Rational subtract(Rational);
    Rational multiply(Rational);
    Rational divide(Rational);
  private:
    int numer;
    int denom;
};

