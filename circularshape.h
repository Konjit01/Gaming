#ifndef CIRCULARSHAPE_H
#define CIRCULARSHAPE_H

#include "shape.h"
#include "polygon.h"

/**
 * @brief The CircularShape class
 */
class CircularShape : public Shape
{
public:
    CircularShape(const Point &center, double r, double minorR = 0);
    ~CircularShape() = default;
    std::shared_ptr<Polygon> getBoundingRectangle() const;
    std::pair<Point, Point> calculateBoundingBox() const override;
    void rotate( const Point& pivot,double angle, bool clockwise) override;
    void move(const Point& delta, double step) override;
    bool isColliding(const std::shared_ptr<Shape>& other) const override;
    Point center() const;
    void setCenter(Point newCenter);
    double getRadius() const;
    void setRadius(double newRadius);

private:
    Point _center;
    double radius;
    double _minorRadius; // For ellipse
};


#endif // CIRCULARSHAPE_H
