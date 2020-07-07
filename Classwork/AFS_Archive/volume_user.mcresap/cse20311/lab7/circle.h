// circle.h
class Circle {
  public:
    Circle();
    Circle(float);
    ~Circle();
    float getRadius();
    void setRadius(float);
    float circumference();
    float area();
  private:
    float radius;
};

