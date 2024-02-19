#ifndef SCENE_H
#define SCENE_H

class Polygon;

#include <vector>
#include "circularshape.h"
#include "linearmath.h"
/**
 * @brief The Scene class
 */
class Scene
{
public:
    Scene(const Scene& other) = delete;
    ~Scene() = default;

    static std::shared_ptr<Scene> getInstance();
    void mapComponentToScene(const std::shared_ptr<Shape>& component);
    void mapPointToScene(Point& point);
    std::vector<Point> hasObstruction(const Point& start, const Point& end, std::shared_ptr<Shape> playingPieces);
    std::pair<Point, bool> areLinesIntersecting(const LinearMath::LineSegment &line1, const LinearMath::LineSegment &line2);
    std::vector<std::pair<Point, std::vector<Point>>> scanPossibleCollision(std::shared_ptr<Polygon> polygon, const Point& endPosition, bool center=false);
    std::vector<std::pair<std::shared_ptr<Shape>, bool>> neigbhorsShapes(const std::shared_ptr<Shape>playerPiece, const Point& endPosition);
    void addComponent(std::pair<std::shared_ptr<Shape>, bool> component);
    std::vector<std::pair<std::shared_ptr<Shape>, bool>> components() const;
    int numOfComponents();
    double endPosition() const;
    void setEndPosition(double newEndPosition);
    std::shared_ptr<Shape> playerPieces() const;
    void setPlayerPieces(std::unique_ptr<std::shared_ptr<Shape> > newPlayerPieces);

private:
    Scene(const Point & origin, double width, double height);
private:
    Point _origin;
    double _width, _height, _endPosition;
    std::vector<std::pair<std::shared_ptr<Shape>, bool>> _components;
    std::unique_ptr<std::shared_ptr<Shape>> _playerPieces;
    const double MARIGIN = 20;
    inline static std::shared_ptr<Scene> instance_;
};

#endif // SCENE_H
