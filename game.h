#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "scene.h"
/**
 * @brief The Game class
 */

using ShapePtrVector = std::vector<std::shared_ptr<Shape>>;

class Game
{
public:
    Game();
    ~Game() = default;

    void initGameEnv(std::shared_ptr<Scene> scene);

    // This function determines if a player can use the shortest path from start to end position.
    void checkPossibleCollisions(std::shared_ptr<Shape>playerPiece, const Point& endPosition);
    void rotatePlayingPieces(ShapePtrVector playerPieces, double step, bool clockwise, std::optional<Point> pivot = std::nullopt);
    void movePlayingPieces(ShapePtrVector playerPieces, const Point& endPosition );
    ShapePtrVector selectPlayerPiecesRandom(int numOfPlayerPieces);
    double moveStepSize() const;
    void setMoveStepSize(double newMoveStepSize);
    Point endPosition() const;
    void setEndPosition(Point newEndPosition);
    double rotateStepSize() const;
    void setRotateStepSize(double newRotateStepSize);

private:
    ShapePtrVector _playerPieces;
    Point _startPosition;
    Point _endPosition;
    double _moveStepSize;
    double _rotateStepSize;
};
#endif // GAME_H
