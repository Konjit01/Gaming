#include "point.h"
#include <cmath>


Point::Point(double x , double y, double z) : _x(x), _y(y), _z(z)
{ }

Point::Point(const Point& other) : _x(other._x), _y(other._y), _z(other._z)
{ }


Point::Point(Point&& other) noexcept : _x(other._x), _y(other._y), _z(other._z)
{
    other._x = 0.0;
    other._y = 0.0;
    other._z = 0.0;
}

Point& Point::operator=(const Point& other)
{
    if (this != &other) {
        _x = other._x;
        _y = other._y;
        _z = other._z;
    }
    return *this;
}

Point& Point::operator=(Point&& other) noexcept
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
        _z = other._z;
        other._x = 0.0;
        other._y = 0.0;
        other._z = 0.0;
    }
    return *this;
}

bool Point::operator<(const Point& other) const
{
    return (_x < other._x) ? true
           : (_x == other._x) ? (_y < other._y)
           : (_y == other._y) ? (_z < other._z)
                              : false;
}

Point Point::operator -(const Point& other) const
{
    return Point(_x - other._x,  _y - other._y,  _z - other._z);
}

bool Point::operator ==(const Point& other) const
{
    return (_x == other._x) && (_y == other._y ) && (_z == other._z);
}

bool Point::operator!=(const Point& other) const
{
    return (_x != other._x) || (_y != other._y) || (_z != other._z);
}

void Point::operator =(Point& other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
}

Point Point::operator -()
{
    return Point(-_x,  -_y,  -_z);
}

Point Point::operator /=( double scalar)
{
    if( scalar )
    {
        return Point(_x /= scalar,  _y /= scalar,  _z/=scalar);
    }
    else
    {
        std::cout  << "Cannot divide by zero."  << std::endl;
        return Point(0, 0, 0);
    }
}

Point Point::operator *=( double scalar)
{
    return Point(_x *= scalar,  _y *= scalar,  _z*=scalar);
}

Point Point::operator *(const Point& other)
{
    return Point(_x * other._x,  _y * other._y,  _z * other._z);
}

Point Point::operator +=(const Point& other)const
{
    Point result = *this;

    result._x += other._x;
    result._y += other._y;
    result._z += other._z;

    return result;
}
Point Point::operator+(const Point& other) const
{
    Point result = *this;

    result._x += other._x;
    result._y += other._y;
    result._z += other._z;

    return result;
}

auto Point::calculateDistance(const Point& other) const -> double {
    auto dx = _x - other._x;
    auto dy = _y - other._y;
    auto dz = _z - other._z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

auto Point::getVectorNorm(Point & vector) -> double
{
    return std::sqrt(vector._x * vector._x + vector._y * vector._y + vector._z * vector._z);
}
double Point::getVectorNorm()
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

void Point::rotate(double angle, const Point& center)
{
    double angle_rad = angle * (M_PI / 180.0);
    double tolerance = 1e-6;
    double cosTheta = cos(angle_rad);
    double sinTheta = sin(angle_rad);

    if (std::abs(cosTheta) < tolerance)
    {
        cosTheta = 0;
    }
    if (std::abs(sinTheta) < tolerance)
    {
        sinTheta = 0;
    }

    double newX = cosTheta * (_x - center._x) - sinTheta * (_y - center._y);
    double newY = sinTheta * (_x - center._x) + cosTheta * (_y - center._y);

    _x = newX + center._x;
    _y = newY + center._y;
}

void Point::translate(const Point& delta)
{
    _x += delta._x;
    _y += delta._y;
    _z += delta._z;
}

Point Point::crossProduct(const Point& other) const
{
    return Point(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}

bool Point::isZero() const
{
    return (_x == 0.0 && _y == 0.0 && _z == 0.0);
}

double Point::dotProduct(const Point& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}

std::ostream& operator<<(std::ostream & ss, const Point& point)
{
    ss << "(" << point._x << ", " << point._y << ", " << point._z << ")";
    return  ss;
}

auto Point::operator <=>(const Point& other) const
{
    // Compare lexicographically by comparing x, y, and z
    return std::tie(_x, _y, _z) <=> std::tie(other._x, other._y, other._z);
}
