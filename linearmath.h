#ifndef LINEARMATH_H
#define LINEARMATH_H
#include "point.h"

class LinearMath
{
public:
    struct LineEquation
    {
        double A, B, C;

    public:
        LineEquation(double aVal, double bVal, double cVal)
            : A(aVal), B(bVal), C(cVal) {}
    };

    struct LineSegment
    {
        LineSegment() {}
        LineSegment(const Point& aStart, const Point& anEnd):
            startPoint{aStart}, endPoint{anEnd}
        {}

        LineEquation getLineEquation() const
        {
            double A = endPoint.getY() - startPoint.getY();
            double B = startPoint.getX() - endPoint.getX();
            double C = -(A * startPoint.getX() + B * startPoint.getY());
            return LineEquation(A, B, C);
        }

        static LineEquation generateLineEquation(double slope, double x0, double y0)
        {
            double intercept = y0 - slope * x0;
            return LineEquation(slope, -1, intercept);
        }

        static double evaluateLineEquation(const LineEquation& equation, double x)
        {
            return equation.A * x + equation.C;
        }

        Point startPoint, endPoint;
    };
};

#endif // LINEARMATH_H
