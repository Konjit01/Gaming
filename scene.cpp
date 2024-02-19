#include "scene.h"
#include "linearmath.h"


Scene::Scene(const Point & origin, double width, double height) :
    _origin{origin}, _width{width}, _height{height}
{

}
std::shared_ptr<Scene> Scene::getInstance()
{
    if (!instance_)
    {
        instance_ = std::shared_ptr<Scene>(new Scene(Point(500, 400), 1000, 800));
    }
    return instance_;
}
void Scene::mapComponentToScene(const std::shared_ptr<Shape>& component)
{
    if (const auto& polygon = std::dynamic_pointer_cast<Polygon>(component))
    {
        std::vector<Point> res;
        res.reserve(polygon->getVertices().size());

        for (const auto& point : polygon->getVertices())
        {
            Point mappedPoint = point;
            mapPointToScene(mappedPoint);
            res.push_back(std::move(mappedPoint));
        }

        polygon->setInitialVertices(std::move(res));
    }
    else if (const auto& circularShape = std::dynamic_pointer_cast<CircularShape>(component))
    {
        Point center = circularShape->center();
        mapPointToScene(center);
    }
    _components.emplace_back(component, false);
}


void Scene::mapPointToScene( Point& point)
{
    point.setX( _origin.getX() + point.getX());
    point.setY( _origin.getY() + point.getY());
    point.setZ( _origin.getZ() + point.getZ());
}

std::vector<Point> Scene::hasObstruction(const Point& start, const Point& end, std::shared_ptr<Shape> playingPieces)
{
    std::vector<Point> intersectionPoints;
    const auto& comps = components();

    for(const auto& component : comps)
    {
        std::shared_ptr<Polygon> polygon = std::dynamic_pointer_cast<Polygon>(component.first);

        if(polygon != playingPieces)
        {
            size_t size = polygon->transformedVertices().size();

            for(size_t i = 0; i < size; i++)
            {
                Point p = (polygon->transformedVertices().at(i));
                Point q = (polygon->transformedVertices().at((i+1) % size));

                const auto& intersectionPoint = areLinesIntersecting(LinearMath::LineSegment(start, end),  LinearMath::LineSegment(p, q));
                if(intersectionPoint.second)
                {
                    intersectionPoints.push_back(intersectionPoint.first);
                }
            }
        }
    }
    return intersectionPoints;
}

std::pair<Point, bool> Scene::areLinesIntersecting(const LinearMath::LineSegment& line1, const LinearMath::LineSegment& line2)
{
    // Get the endpoints of the first line segment
    const Point& p1 = line1.startPoint;
    const Point& p2 = line1.endPoint;

    // Get the dpoints of the second line segment
    const Point& p3 = line2.startPoint;
    const Point& p4 = line2.endPoint;

    // Calculate the denominator for the intersection point formula
    double denominator = (p4.getY() - p3.getY()) * (p2.getX() - p1.getX()) - (p4.getX() - p3.getX()) * (p2.getY() - p1.getY());

    // Check if the lines are parallel or coincident (denominator is close to zero)
    if (std::abs(denominator) < std::numeric_limits<double>::epsilon())
    {
        return std::make_pair(Point(), false);
    }

    // Calculate the intersection parameters
    double ua = ((p4.getX() - p3.getX()) * (p1.getY() - p3.getY()) - (p4.getY() - p3.getY()) * (p1.getX() - p3.getX())) / denominator;
    double ub = ((p2.getX() - p1.getX()) * (p1.getY() - p3.getY()) - (p2.getY() - p1.getY()) * (p1.getX() - p3.getX())) / denominator;

    double tolerance = 1e-6;

    if (ua >= -tolerance && ua <= 1 + tolerance && ub >= -tolerance && ub <= 1 + tolerance)
    {
        Point intersectionPoint;
        intersectionPoint.setX( p1.getX() + ua * (p2.getX() - p1.getX()));
        intersectionPoint.setY(p1.getY() + ua * (p2.getY() - p1.getY()));
        intersectionPoint.setZ( p1.getZ() + ua * (p2.getZ() - p1.getZ()));
        return std::make_pair(intersectionPoint, true);
    }
    return std::make_pair(Point(), false);
}

std::vector<std::pair<Point, std::vector<Point>>> Scene::scanPossibleCollision(std::shared_ptr<Polygon> polygon, const Point& endPosition, bool center)
{
    std::vector<std::pair<Point, std::vector<Point>>> _pointsOfPossibleCollisions;

    const auto startPosition = polygon->calculatePolygonCenter();
    double A = 0, B = 0, slope = 0;

    A = startPosition.getY() - endPosition.getY();
    B = startPosition.getX() - endPosition.getX();
    slope = A/B;

    size_t  size =  polygon->transformedVertices().size();
    for(size_t i = 0; i < size; ++i)
    {
        std::vector<Point> intersections;

        if(!center)
        {
            auto v = polygon->transformedVertices().at(i);
            auto eq = LinearMath::LineSegment::generateLineEquation(slope, v.getX(), v.getY());
            auto val = LinearMath::LineSegment::evaluateLineEquation(eq, endPosition.getX());
            const Point p(endPosition.getX(), val);

            intersections = hasObstruction(v, p, polygon);
            if(intersections.size())
            {
                _pointsOfPossibleCollisions.push_back(std::make_pair(v, intersections));
            }
        }
        else
        {
            intersections = Scene::getInstance()->hasObstruction(startPosition, endPosition, polygon);
            if(intersections.size())
            {
                _pointsOfPossibleCollisions.push_back(std::make_pair(startPosition, intersections));
            }
        }
    }
    return _pointsOfPossibleCollisions;
}

std::vector<std::pair<std::shared_ptr<Shape>, bool>> Scene::neigbhorsShapes(const std::shared_ptr<Shape>playerPiece, const Point& endPosition)
{
    std::vector<std::pair<std::shared_ptr<Shape>, bool>> neigbhors;
    std::shared_ptr<Polygon> polygon = std::dynamic_pointer_cast<Polygon>(playerPiece);

    double disatnce = endPosition.calculateDistance(polygon->calculatePolygonCenter());
    for(const  auto& comp : components())
    {
        std::shared_ptr<Polygon> other = std::dynamic_pointer_cast<Polygon>(comp.first);
        if(polygon != other)
        {
            double otherDisatnce = abs((other->calculatePolygonCenter() - polygon->calculatePolygonCenter()).getVectorNorm());

            if(otherDisatnce < disatnce + MARIGIN)
            {
                neigbhors.push_back(comp);
            }
        }
    }
    return neigbhors;
}

void Scene::addComponent(std::pair<std::shared_ptr<Shape>, bool> component)
{
    _components.push_back(component);
}

std::vector<std::pair<std::shared_ptr<Shape>, bool>> Scene::components() const
{
    return _components;
}

int Scene::numOfComponents()
{
    return _components.size();
}

double Scene::endPosition() const
{
    return _endPosition;
}

void Scene::setEndPosition(double newEndPosition)
{
    _endPosition = newEndPosition;
}

std::shared_ptr<Shape> Scene::playerPieces() const
{
    if (_playerPieces)
        return *_playerPieces;

    return nullptr;
}


void Scene::setPlayerPieces(std::unique_ptr<std::shared_ptr<Shape> > newPlayerPieces)
{
    _playerPieces = std::move(newPlayerPieces);
}



