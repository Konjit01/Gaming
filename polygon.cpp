#include "polygon.h"

std::string red = "\033[31m";
std::string green = "\033[32m";
std::string magenta = "\033[35m";
std::string reset = "\033[0m";

Polygon::Polygon(const std::initializer_list<Point> &initialVertices) : _initialVertices {std::vector<Point>(initialVertices)}
{
    std::cout << "Class Polygon() " << std::endl;
    _transformedVertices = std::vector<Point>();
}

void Polygon::move(const Point& destination, double stepSize)
{
    Point moveVector = destination - _center;

    double distance = moveVector.getVectorNorm();
    double tolerance = 1e-6; // suitable tolerance for considering the destination reached

    if (distance < tolerance)
    {
        std::cout << green << "Already at the destination." << reset << std::endl;
        return;
    }
    // Check for potential collision before moving
    std::shared_ptr<Shape> sharedThis = shared_from_this();
    for (const auto& otherComponent : Scene::getInstance()->neigbhorsShapes(sharedThis, destination))
    {
        const auto& otherPolygon = std::dynamic_pointer_cast<Polygon>(otherComponent.first);
        if (this != otherPolygon.get())
        {
            if (intersects(otherPolygon, destination))
            {
                std::cout << red << "Collision detected. Cannot move to the destination." << reset << std::endl;
                return;
            }
        }
    }

    int numSteps = static_cast<int>(distance / stepSize);
    if (numSteps == 0)
        numSteps = 1;

    moveVector /= numSteps;

    _transformedVertices = _initialVertices;
    int iteration = 1;

    while (_center != destination)
    {
        for (int step = 0; step < numSteps; ++step)
        {
            for (auto& point : _transformedVertices)
            {
                point.translate(moveVector);
            }
            // Check for collision after each step
            std::shared_ptr<Shape> sharedThis = shared_from_this();
            for (const auto& otherComponent : Scene::getInstance()->neigbhorsShapes(sharedThis, destination))
            {
                std::shared_ptr<Polygon> otherPolygon = std::dynamic_pointer_cast<Polygon>(otherComponent.first);
                if (this != otherPolygon.get())
                {
                    if (intersects(otherPolygon, destination))
                    {
                        std::cout << red <<"Collision detected. Change movment direction." <<  reset << std::endl;
                        return;
                    }
                }
            }

            iteration++;
            _center = calculatePolygonCenter();
        }

        double currentDistance = (_center - destination).getVectorNorm();

        if (currentDistance <= tolerance)
        {
            std::cout << green << "Reached your destination after " << iteration << " steps." << reset << std::endl;
            break;
        }
        if (iteration > 1 && currentDistance > distance)
        {
            std::cout <<  "Unable to reach the destination." << std::endl;
            break;
        }
        distance = currentDistance;
    }
}

void Polygon::rotate(const Point& pivot, double step, bool clockwise)
{
    double currentAngle = 0.0;
    double rotationStep = clockwise ? step : -step;

    while (currentAngle < 360.0)
    {
        // Apply rotation to the transformed vertices
        _transformedVertices = _initialVertices;
        for (Point& point : _transformedVertices)
        {
            point.rotate(rotationStep, pivot);
        }
        _center = calculatePolygonCenter();

        // Check for collision before rotation
        for (const auto& otherComponent : Scene::getInstance()->components())
        {
            std::shared_ptr<Polygon> otherPolygon = std::dynamic_pointer_cast<Polygon>(otherComponent.first);
            if (this != otherPolygon.get())
            {
                if (intersects(otherPolygon, Point(0,0,0)))
                {
                    std::cout << magenta << "Collision detected. Change rotation angle." << std::endl<< std::endl;
                    return;
                }
            }
        }
        // Check for collision after rotation
        for (const auto& otherComponent : Scene::getInstance()->components())
        {
            std::shared_ptr<Polygon> otherPolygon = std::dynamic_pointer_cast<Polygon>(otherComponent.first);
            if (this != otherPolygon.get())
            {
                if (intersects(otherPolygon, Point(0,0,0)))
                {
                    std::cout << "Collision detected. Change rotation angle." << std::endl;
                    return;
                }
            }
        }
        currentAngle += std::abs(rotationStep);
    }
}

std::pair<const std::vector<Point>&, const std::vector<Point>&> Polygon::getPoints() const
{
    return {_initialVertices, _transformedVertices};
}

std::shared_ptr<Polygon> Polygon::getBoundingRectangle() const
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

std::pair<Point, Point> Polygon::calculateBoundingBox() const
{
    const auto& vertices = _transformedVertices.empty() ? _initialVertices : _transformedVertices;

    std::vector<double> xValues;
    std::vector<double> yValues;
    std::vector<double> zValues;

    for (const auto& point : vertices)
    {
        xValues.push_back(point.getX());
        yValues.push_back(point.getY());
        zValues.push_back(point.getZ());
    }

    double minX = *std::min_element(xValues.begin(), xValues.end());
    double minY = *std::min_element(yValues.begin(), yValues.end());
    double minZ = *std::min_element(zValues.begin(), zValues.end());
    double maxX = *std::max_element(xValues.begin(), xValues.end());
    double maxY = *std::max_element(yValues.begin(), yValues.end());
    double maxZ = *std::max_element(zValues.begin(), zValues.end());

    Point minPoint(minX, minY, minZ);
    Point maxPoint(maxX, maxY, maxZ);


    return {minPoint, maxPoint};
}

// Collision detection between any two polygons' bounding rectangles
bool Polygon::collidesWithOther(const std::shared_ptr<Shape>& other) const
{
    auto [min1, max1] = calculateBoundingBox();
    auto [min2, max2] = other->calculateBoundingBox();

    // Check if the bounding boxes intersect

    if (max1.getX() < min2.getX() || min1.getX() > max2.getX())
        return false;
    if (max1.getY() < min2.getY() || min1.getY() > max2.getY())
        return false;
    if (max1.getZ() < min2.getZ() || min1.getZ() > max2.getZ())
        return false;

    return true;
}

std::vector<Point> Polygon::getEdges() const
{
    std::vector<Point> edges;
    size_t size = transformedVertices().size();
    for(size_t i = 0; i < size; i++)
    {
        const auto& vertex1 = transformedVertices().at(i);
        const auto& vertex2 = transformedVertices().at( (i+1) % size );

        edges.emplace_back(vertex2 - vertex1);
    }
    return edges;
}

bool Polygon::intersects(const std::shared_ptr<Polygon>& other, const Point& destination) const
{
    const std::vector<Point>& verticesA =  transformedVertices();
    const std::vector<Point>& verticesB = other->transformedVertices();

    const std::vector<Point>& edgesA = getEdges();
    const std::vector<Point>& edgesB = other->getEdges();

    // Check overlap on all axes of polygon A
    for (const Point& edge : edgesA)
    {
        Point axis = calculateEdgeNormal(edge);
        float minA = INFINITY;
        float maxA = -INFINITY;
        for (const Point& vertex : verticesA)
        {
            if (vertex == destination) continue;
            float projection = axis.dotProduct(vertex);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        // Project vertices of polygon B onto the axis
        float minB = INFINITY;
        float maxB = -INFINITY;
        for (const Point& vertex : verticesB)
        {
            if (vertex == destination) continue;
            float projection = axis.dotProduct(vertex);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        // Check for overlap
        if (maxA < minB || maxB < minA)
        {
            return false;
        }
    }

    // Check overlap on all axes of polygon B
    for (const Point& edge : edgesB)
    {
        Point axis = calculateEdgeNormal(edge);

        float minA = INFINITY;
        float maxA = -INFINITY;
        for (const Point& vertex : verticesA)
        {
            if (vertex == destination) continue;

            float projection = axis.dotProduct(vertex);
            minA = std::min(minA, projection);
            maxA = std::max(maxA, projection);
        }

        // Project vertices of polygon B onto the axis
        float minB = INFINITY;
        float maxB = -INFINITY;
        for (const Point& vertex : verticesB)
        {
            if (vertex == destination) continue;
            float projection = axis.dotProduct(vertex);
            minB = std::min(minB, projection);
            maxB = std::max(maxB, projection);
        }

        // Check for overlap
        if (maxA < minB || maxB < minA)
        {
            return false;  // No overlap, polygons are not colliding
        }
    }

    return true;  // Overlap on all axes, polygons are colliding
}

Point Polygon::calculatePolygonCenter()
{
    if (!_transformedVertices.size())
    {
        if (!_initialVertices.size())
        {
            return Point(0, 0, 0);
        }

        double sumX = 0, sumY = 0, sumZ = 0;
        for (const auto& vertex : _initialVertices)
        {
            sumX += vertex.getX();
            sumY += vertex.getY();
            sumZ += vertex.getZ();
        }

        Point point(sumX / _initialVertices.size(), sumY / _initialVertices.size(), sumZ / _initialVertices.size());

        setCenter(point);

        return point;
    }

    // Calculate center based on transformed vertices
    double sumX = 0, sumY = 0, sumZ = 0;
    for (const auto& vertex : _transformedVertices)
    {
        sumX += vertex.getX();
        sumY += vertex.getY();
        sumZ += vertex.getZ();
    }

    Point point(sumX / _transformedVertices.size(), sumY / _transformedVertices.size(), sumZ / _transformedVertices.size());

    setCenter(point);

    return point;
}

std::vector<Point> Polygon::getVertices() const
{
    return  _initialVertices;
}

std::vector<Point> Polygon::transformedVertices() const
{
    return  _transformedVertices.empty() ? _initialVertices : _transformedVertices;
}


std::vector<Point> Polygon::initialVertices() const
{
    return _initialVertices;
}

void Polygon::setInitialVertices(const std::vector<Point> &newInitialVertices)
{
    _initialVertices = newInitialVertices;
}

inline const Point& Polygon::getCenter() const
{
    return _center;
}
void Polygon::setCenter(const Point& center)
{
    _center = center;
}


Point Polygon::calculateEdgeNormal(const Point& edge) const
{
    float nx = edge.getY();
    float ny = -edge.getX();
    float length = std::sqrt(nx * nx + ny * ny);
    if (length != 0) {
        nx /= length;
        ny /= length;
    }
    return Point(nx, ny);
}

