#include <iostream>

#include "polygon.h"
#include "game.h"

int main()
{

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
