#ifndef POLYGON_H
#define POLYGON_H

#include <memory>
#include "point.h"
#include "shape.h"
#include "scene.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <cmath>
#include <ranges>
#include <random>
#include <optional>
#include <unordered_set>

/**
 * @brief The Polygon class
 */
class Polygon : public Shape , public std::enable_shared_from_this<Polygon>
{
public:
    Polygon(const std::initializer_list<Point> & initialVertices);
    Polygon(const Polygon& other) = default;
    ~Polygon() = default;
    Polygon& operator =(const Polygon& other) = default;

    void rotate(const Point &pivot, double step, bool clockwise);
    std::pair<const std::vector<Point>&, const std::vector<Point>&> getPoints() const;
    std::shared_ptr<Polygon> getBoundingRectangle() const ;
    std::pair<Point, Point> calculateBoundingBox() const override;

    // Collision detection between any two polygons' bounding rectangles
    bool collidesWithOther(const std::shared_ptr<Shape> &other) const;
    std::vector<Point> getEdges() const;
    bool intersects(const std::shared_ptr<Polygon>& other, const Point& destination) const;
    Point calculatePolygonCenter();
    std::vector<Point> getVertices() const;
    std::vector<Point> transformedVertices() const;
    std::vector<Point> initialVertices() const;
    void setInitialVertices(const std::vector<Point> &newInitialVertices);
    inline const Point& getCenter() const;
    void setCenter(const Point& center);
    void move(const Point& destination, double stepSize) override;
    bool isColliding(const std::shared_ptr<Shape>& other) const override
    {
      return false;
    }
private:
    Point calculateEdgeNormal(const Point& edge) const;
    std::vector<Point> _initialVertices;
    std::vector<Point> _transformedVertices;
    Point _center;
};

#endif // POLYGON_H
