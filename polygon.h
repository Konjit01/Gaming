/**
 * @file Polygon.h
 *
 * @brief Defines the Polygon class, representing a polygon in three-dimensional space.
 */

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
 * @class Polygon
 * @brief Represents a polygon in three-dimensional space.
 * @details Inherits from Shape and enables shared ownership using enable_shared_from_this.
 */
class Polygon : public Shape , public std::enable_shared_from_this<Polygon>
{
public:
    /**
    * @brief Constructor for Polygon.
    *
    * Initializes a Polygon with the provided list of initial vertices.
    *
    * @param initialVertices A list of initial vertices to initialize the Polygon.
    */
    Polygon(const std::initializer_list<Point> & initialVertices);

    /**
    * @brief Copy constructor for Polygon.
    * @param other The Polygon to be copied.
    */
    Polygon(const Polygon& other) = default;

    ~Polygon() = default;
    Polygon& operator =(const Polygon& other) = default;
    /**
    * @brief Moves the Polygon towards a destination point.
    *
    * This method moves the Polygon towards a specified destination point by applying
    * a series of steps. The step size is determined by the `stepSize` parameter.
    *
    * @param destination The destination point to which the Polygon should be moved.
    * @param stepSize The size of each movement step.
    */

    void move(const Point& destination, double stepSize) override;
    /**
    * @brief Rotates the Polygon around a pivot point.
    *
    * This method rotates the Polygon around a specified pivot point by applying
    * a rotation step. The rotation direction (clockwise or counterclockwise) is
    * determined by the `clockwise` parameter.
    *
    * @param pivot The pivot point around which the Polygon will be rotated.
    * @param step The rotation step in degrees.
    * @param clockwise Flag indicating the rotation direction (clockwise if true, counterclockwise otherwise).
    */

    void rotate(const Point &pivot, double step, bool clockwise);
    /**
    * @brief Retrieves a shared pointer to a bounding rectangle Polygon. This function is similar to CircularShape::getBoundingRectangle()
    *
    * This method calculates the bounding box of the Polygon and constructs a new Polygon representing
    * the bounding rectangle. The shared pointer to the bounding rectangle Polygon is then returned.
    *
    * The bounding rectangle is created using the minimum (min) and maximum (max) corners of the bounding
    * box obtained from the `calculateBoundingBox` method.
    *
    * @return A shared pointer to a new Polygon representing the bounding rectangle.
    *         If no vertices are available for the bounding box, a null shared pointer is returned.
    *
    * @note This function was initialy implemented to detect collision between any two shapes.
    * @attention Thus all shapes are considered convex.
    * @warning This method may cause false collison detection.
    * @see intersects()
    */
    std::shared_ptr<Polygon> getBoundingRectangle() const ;

    /**
    * @brief Calculates the bounding box of the Polygon.
    *
    * This method calculates the bounding box of the Polygon based on either the initial vertices
    * or the transformed vertices, whichever is available. If neither is available, an empty pair
    * is returned.
    *
    * The bounding box is represented by a pair of Points: the minimum (minPoint) and maximum (maxPoint)
    * corners of the box.
    *
    * @return A pair representing the minimum and maximum corners of the bounding box.
    *         If no vertices are available, an empty pair is returned.
    */
    std::pair<Point, Point> calculateBoundingBox() const override;

    // Collision detection between any two polygons' bounding rectangles
    bool collidesWithOther(const std::shared_ptr<Shape> &other) const;
    std::vector<Point> getEdges() const;

    /**
    * @brief Checks if the Polygon intersects with another Polygon at a specific destination.
    *
    * This function determines whether the calling Polygon intersects with the provided Polygon
    * when both are positioned at the specified destination point.
    *
    * @param other A shared pointer to the other Polygon for intersection comparison.
    * @param destination The destination point where both Polygons are positioned for comparison.
    * @return True if the Polygons intersect at the specified destination, otherwise false.
    */
    bool intersects(const std::shared_ptr<Polygon>& other, const Point& destination) const;

    /**
    * @brief Calculates the center of the Polygon.
    *
    * This method calculates the center of the Polygon based on either the initial vertices
    * or the transformed vertices, whichever is available. If neither is available, a default
    * Point at the origin (0, 0, 0) is returned.
    *
    * @return The calculated center Point of the Polygon.
    */
    Point calculatePolygonCenter();

    bool isColliding(const std::shared_ptr<Shape>& other) const override
    {
        return false;
    }
    std::vector<Point> getVertices() const;
    std::vector<Point> transformedVertices() const;
    std::vector<Point> initialVertices() const;
    std::pair<const std::vector<Point>&, const std::vector<Point>&> getPoints() const;
    void setInitialVertices(const std::vector<Point> &newInitialVertices);
    inline const Point& getCenter() const;
    void setCenter(const Point& center);

private:
    Point calculateEdgeNormal(const Point& edge) const;
    std::vector<Point> _initialVertices;
    std::vector<Point> _transformedVertices;
    Point _center;
};

#endif // POLYGON_H
