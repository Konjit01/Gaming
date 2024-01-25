#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include "point.h"
/**
 * @brief The Shape class
 */

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void rotate(const Point& pivot, double angle, bool clockwise) = 0;
    virtual void move(const Point& destination, double stepSize) = 0;
    virtual bool isColliding(const std::shared_ptr<Shape>& other) const = 0;
    virtual std::pair<Point, Point> calculateBoundingBox() const = 0;
    void draw(){}
};

#endif // SHAPE_H
