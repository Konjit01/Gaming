#include <iostream>

using namespace std;
#include "polygon.h"
#include "game.h"

int main()
{
    auto square = std::make_shared<Polygon>(std::initializer_list<Point>
                                            {
                                                std::move(Point(30.0, -30.0, 0.0)),
                                                std::move(Point(35.0, -30.0, 0.0)),
                                                std::move(Point(30.0, -35.0, 0.0)),
                                                std::move(Point(35.0, -35.0, 0.0))
                                            });

    auto rect1 = std::make_unique<Polygon>(std::initializer_list<Point>
                                           {
                                               std::move(Point(-3.36603, 11.1603, 0)),
                                               std::move(Point(6.16025, 11.1603, 0)),
                                               std::move(Point(6.16025, 3.83013, 0)),
                                               std::move(Point(-3.36603, 3.83013, 0))
                                           });



    const Point p1(30.0, -30.0, 0.0);
    const Point p2(35.0, -30.0, 0.0);

    std::cout << p1.calculateDistance(p2) << std::endl;
    auto res = p1 <=> p2;

    if(res == 0)
    {
        std::cout << "They are equal " << std::endl;
    }else
    {
        std::cout << "They not are equal " << std::endl;
    }
    const auto& scene = Scene::getInstance();

    Game game;

    int numOfPlayingPieces = 2;
    double moveStep = 0.2;
    double angle = 5;
    Point rotateAt(0,0,0);
    bool rotateCW = true;

    game.setEndPosition(Point(-12,8,0));
    game.initGameEnv(scene);
    const auto& playerPieces = game.selectPlayerPiecesRandom(numOfPlayingPieces);

    for(const auto& playingPiece : playerPieces)
    {
        game.checkPossibleCollisions(playingPiece, game.endPosition());
    }
    game.setMoveStepSize(moveStep);
    game.setRotateStepSize(angle);
    game.movePlayingPieces(playerPieces, game.endPosition());
    game.rotatePlayingPieces(playerPieces, angle, rotateCW, rotateAt);
    return 0;
}
