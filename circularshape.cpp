#include "circularshape.h"



CircularShape::CircularShape(const Point &center, double r, double minorR) : _center{center}, radius(r), _minorRadius(minorR)
{
}

std::shared_ptr<Polygon> CircularShape::getBoundingRectangle() const
{
    auto [min, max] = calculateBoundingBox();

    auto rect = std::make_shared<Polygon>(std::initializer_list<Point>
                                          {
                                              (Point(min.getX(), max.getY())),
                                              (max),
                                              (Point(max.getX(), min.getY())),
                                              (min)
                                          });

    return rect;
}

std::pair<Point, Point> CircularShape::calculateBoundingBox() const
{

    Point center = _center;
    double majorRadius = radius;
    double minorRadius = _minorRadius;

    // Calculate the coordinates of the top-left corner and bottom-right corner
    // of the bounding box based on the and circle and ellipse properties
    double left = 0, top = 0, right = 0, bottom = 0;
    if(minorRadius)
    {
        left   = center.getX() - majorRadius;
        top    = center.getY() - minorRadius;
        right  = center.getX() + majorRadius;
        bottom = center.getY() + minorRadius;
    }else
    {
        left   = center.getX() - majorRadius;
        top    = center.getY() - majorRadius;
        right  = center.getX() + majorRadius;
        bottom = center.getY() + majorRadius;
    }

    return {Point(left, top),  Point(right, bottom)};
}

void CircularShape::rotate(const Point &pivot, double angle, bool clockwise)
{
    // Implementation of rotation for CircularShape
}

void CircularShape::move(const Point &delta, double step)
{
    // Implementation of movement for CircularShape
}

bool CircularShape::isColliding(const std::shared_ptr<Shape> &other) const
{
    // Implementation of collision detection for CircularShape
    return false; // Replace with actual implementation
}

Point CircularShape::center() const
{
    return _center;
}

void CircularShape::setCenter(Point newCenter)
{
    _center = newCenter;
}

double CircularShape::getRadius() const
{
    return radius;
}

void CircularShape::setRadius(double newRadius)
{
    radius = newRadius;
}
