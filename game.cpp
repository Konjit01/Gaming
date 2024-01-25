#include "game.h"

Game::Game() {}


ShapePtrVector createPolygons()
{
    ShapePtrVector shapes;

    //Polygon 0
    auto rect = std::make_unique<Polygon>(std::initializer_list<Point>
                                          {
                                              std::move(Point(-12.0,-10.0, 0.0)),
                                              std::move(Point(-12.0, -5.0, 0.0)),
                                              std::move(Point(-4.0, -10.0, 0.0)),
                                              std::move(Point(-5.0, -15.0, 0.0))
                                          });

    shapes.push_back(std::move(rect));

    // Polygon 1
    auto rect1 = std::make_unique<Polygon>(std::initializer_list<Point>
                                           {
                                               std::move(Point(-3.36603, 11.1603, 0)),
                                               std::move(Point(6.16025, 11.1603, 0)),
                                               std::move(Point(6.16025, 3.83013, 0)),
                                               std::move(Point(-3.36603, 3.83013, 0))
                                           });

    shapes.push_back(std::move(rect1));

    // Polygon 2
    auto triangle = std::make_unique<Polygon>(std::initializer_list<Point>
                                              {
                                                  std::move(Point(-1.0, 5.0, 0.0)),
                                                  std::move(Point(5.0, 10.0, 0.0)),
                                                  std::move(Point(10.0, 5.0, 0.0))
                                              });

    shapes.push_back(std::move(triangle));
    // Polygon 3
    auto rect2 = std::make_unique<Polygon>(std::initializer_list<Point>
                                           {
                                               std::move(Point(5.0, -1.0, 0.0)),
                                               std::move(Point(18.0, 2.0, 0.0)),
                                               std::move(Point(18.0, -10.0, 0.0)),
                                               std::move(Point(30.0, 0.0, 0.0))
                                           });

    shapes.push_back(std::move(rect2));
    // Polygon 4
    auto pentagon = std::make_unique<Polygon>(std::initializer_list<Point>
                                              {
                                                  std::move(Point(-30.0, 15.0, 0.0)),
                                                  std::move(Point(-20.0, 15, 0.0)),
                                                  std::move(Point(-30.0, 8.0, 0.0)),
                                                  std::move(Point(-15.0, 0.0, 0.0)),
                                                  std::move(Point(-12.0, 8.0, 0.0))
                                              });

    shapes.push_back(std::move(pentagon));
    // Polygon 5
    auto triangle2 = std::make_unique<Polygon>(std::initializer_list<Point>
                                               {
                                                   std::move(Point(-30.0, -3.0, 0.0)),
                                                   std::move(Point(-34.0, -5.0, 0.0)),
                                                   std::move(Point(-27.0, -9.0, 0.0))
                                               });

    shapes.push_back(std::move(triangle2));

    // Polygon 6
    auto square = std::make_unique<Polygon>(std::initializer_list<Point>
                                            {
                                                std::move(Point(30.0, -30.0, 0.0)),
                                                std::move(Point(35.0, -30.0, 0.0)),
                                                std::move(Point(30.0, -35.0, 0.0)),
                                                std::move(Point(35.0, -35.0, 0.0))
                                            });

    shapes.push_back(std::move(square));

    //Polygon 7
    auto rect3 = std::make_unique<Polygon>(std::initializer_list<Point>
                                           {
                                               std::move(Point(-40.0, -30.0, 0.0)),
                                               std::move(Point(-25.0, -30.0, 0.0)),
                                               std::move(Point(-40.0, -35.0, 0.0)),
                                               std::move(Point(-25.0, -35.0, 0.0))
                                           });

    shapes.push_back(std::move(rect3));

    auto ellipse = std::make_shared<CircularShape>(std::move(Point(45, 30, 0)), 5.0, 3.0);
    auto circle = std::make_shared<CircularShape>(std::move(Point(-45, 10, 0)), 5.0);
    return shapes;
}

void Game::initGameEnv(std::shared_ptr<Scene> scene)
{
    const auto& polygons = createPolygons();
    for(const auto& polygon : polygons)
    {
        scene->mapComponentToScene(polygon);
    }
}

void Game::checkPossibleCollisions(std::shared_ptr<Shape> playerPiece, const Point &endPosition)
{
    std::shared_ptr<Polygon> polygon = std::dynamic_pointer_cast<Polygon>(playerPiece);
    const auto& collisionPoints = Scene::getInstance()->scanPossibleCollision(polygon, endPosition);

    std::cout << "\nFor the playing piece(polygon vertices): "  << std::endl;
    for(const auto& player: polygon->transformedVertices())
    {
        std::cout  << " ->" << player  << std::endl;
    }
    //std::cout << std::endl;
    if(collisionPoints.size())
    {
        std::cout <<  "there're obstruction shape(s) along the way to " << endPosition << std::endl;
    }
    else
    {
        std::cout << "there aren't obstruction shape(s) along the way to " << endPosition  << std::endl;
    }
    std::cout << std::endl;
}

void Game::rotatePlayingPieces(ShapePtrVector playerPieces, double step, bool clockwise, std::optional<Point> pivot)
{
    for (const auto& playerPiece : playerPieces)
    {
        std::shared_ptr<Polygon> polygon = std::dynamic_pointer_cast<Polygon>(playerPiece);

        Point rotateAt;
        if(pivot.has_value())
        {
            rotateAt = pivot.value();
        }
        else
        {
            //rotateAt = polygon->getCenter();
        }
        polygon->rotate(rotateAt, step, clockwise);
    }

}

void Game::movePlayingPieces(ShapePtrVector playerPieces, const Point &endPosition)
{
    for (const auto& playerPiece : playerPieces)
    {
        std::shared_ptr<Polygon> polygon = std::dynamic_pointer_cast<Polygon>(playerPiece);
        polygon->move(endPosition, _moveStepSize);
    }
}

ShapePtrVector Game::selectPlayerPiecesRandom(int numOfPlayerPieces)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, Scene::getInstance()->components().size() - 1);
    std::unordered_set<int> selectedIndices;

    while (selectedIndices.size() < numOfPlayerPieces)
    {
        int randomComponent = dist(rng);

        if (selectedIndices.find(randomComponent) == selectedIndices.end())
        {
            selectedIndices.insert(randomComponent);
            Scene::getInstance()->components().at(randomComponent).second = true;
            _playerPieces.push_back(Scene::getInstance()->components().at(randomComponent).first);
        }
    }

    return std::move(_playerPieces);
}

double Game::moveStepSize() const
{
    return _moveStepSize;
}

void Game::setMoveStepSize(double newMoveStepSize)
{
    _moveStepSize = newMoveStepSize;
}

Point Game::endPosition() const
{
    return _endPosition;
}

void Game::setEndPosition(Point newEndPosition)
{
    _endPosition = newEndPosition;
    Scene::getInstance()->mapPointToScene(_endPosition);

}

double Game::rotateStepSize() const
{
    return _rotateStepSize;
}

void Game::setRotateStepSize(double newRotateStepSize)
{
    _rotateStepSize = newRotateStepSize;
}
