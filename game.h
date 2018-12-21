#pragma once

#include <QtWidgets>
#include "gameboard.h"
#include "interface.h"

class Game
{
private:
    Interface *userInt;
    GameBoard *gb;
public:
    Game();

    GameBoard *getGB();
    void delay(int);
};

extern Game *game;
