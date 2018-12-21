#include "game.h"
#include "ai.h"

Game::Game()
{
    userInt = new Interface();
    gb = new GameBoard();
    userInt->show();
}

GameBoard *Game::getGB()
{
    return gb;
}

void Game::delay(int sec)
{
    QTime dieTime= QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
