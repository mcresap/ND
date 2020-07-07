class Money {
    friend ostream & operator<< (ostream &, Money &);
    friend istream & operator>> (istream &, Money &);
  public:
    Money();
    Money(int, int);
    ~Money();
    int getDollar();
    int getCent();
    void setDollar(int);
    void setCent(int);
    void setMoney(int, int);
    void convert();
    Money operator+(Money);
    Money operator-(Money);
    bool operator> (Money);
  private:
    int dollar;
    int cent;
};
