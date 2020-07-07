#include "circle.h"
#include <math.h>

Circle::Circle()
{
    radius=7;
}

Circle::Circle(float r)
{
    radius=r;
}

Circle::~Circle()
{ }

float Circle::getRadius()
{
    return radius;
}

void Circle::setRadius(float r)
{
    radius=r;
}

float Circle::circumference()
{
    return 2*radius*(atan(1)*4);
}

float Circle::area()
{
    return pow(radius, 2)*(atan(1)*4);
}

