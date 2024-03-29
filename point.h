/**
 * @file Point.h
 *
 * @brief Defines the Point class, representing a point in three-dimensional space.
 */

#ifndef POINT_H
#define POINT_H
#include <compare>
#include <iostream>
#include <tuple>

/**
 * @class Point
 * @brief Represents a point in three-dimensional space.
 */

class Point
{
public:
    /**
     * @brief Point
     * @param x
     * @param y
     * @param z
     */
    Point(double x = 0.0, double y = 0.0, double z = 0.0);
    Point(const Point& other);
    Point(Point&& other) noexcept;
    ~Point() = default;
    Point& operator=(const Point& other);
    Point& operator=(Point&& other) noexcept;

    inline constexpr double getX() const { return _x; }
    inline constexpr double getY() const { return _y; }
    inline constexpr double getZ() const { return _z; }

    void setX(double x) { _x = x; }
    void setY(double y) { _y = y; }
    void setZ(double z) { _z = z; }

    friend std::ostream& operator<<(std::ostream & ss, const Point& point);

    auto operator<=>(const Point& other) const;
    bool operator<(const Point& other) const;
    Point operator -(const Point& other) const;
    bool operator ==(const Point& other) const;
    bool operator!=(const Point& other) const;
    void operator =(Point& other);

    Point operator -();
    Point operator /=( double scalar);
    Point operator *=( double scalar);
    Point operator *(const Point& other);
    Point operator +=(const Point& other)const;
    Point operator+(const Point& other) const;
    auto calculateDistance(const Point& other) const -> double;

    auto getVectorNorm(Point & vector) ->double;
    double getVectorNorm();
    void rotate(double angle, const Point& center);
    void translate(const Point& delta);
    Point crossProduct(const Point& other) const;
    bool isZero() const;
    double dotProduct(const Point& other) const;

private:
    double _x,  _y, _z;
};


#endif // POINT_H
