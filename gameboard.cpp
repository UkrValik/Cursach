#include "gameboard.h"
#include "game.h"
#include "checker.h"
#include "ai.h"

GameBoard::GameBoard(QWidget *)
{
    hasActiveChecker = false;
    myLayout = new QGridLayout;
    myLayout->setContentsMargins(window()->width() / 10, 0, window()->width() / 10, 0);
    myLayout->setSpacing(0);
    cells.resize(8);
    redCheckers.resize(12);
    blueCheckers.resize(12);
    int redCheckersCounter = 0;
    int blueCheckersCounter = 0;
    for (int i = 0; i < 8; ++i) {
        cells[i].resize(8);
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2) {
                cells[i][j] = new Cell(Qt::white, i, j);
            }
            else {
                cells[i][j] = new Cell(Qt::black, i, j);
            }
            QObject::connect(cells.at(i).at(j), SIGNAL(moveThisChecker(Checker*, int, int)), this, SLOT(moveChecker(Checker*, int, int)));
            myLayout->addWidget(cells[i][j], i, j);
            if (cells[i][j]->getColor() == Qt::white && i < 3) {
                redCheckers[redCheckersCounter] = new Checker(i, j, Qt::red);
                myLayout->addWidget(redCheckers[redCheckersCounter], i, j);
                myLayout->setAlignment(redCheckers[redCheckersCounter], Qt::AlignCenter);
                redCheckersCounter++;
            }
            if (cells[i][j]->getColor() == Qt::white && i > 4) {
                blueCheckers[blueCheckersCounter] = new Checker(i, j, Qt::blue);
                myLayout->addWidget(blueCheckers[blueCheckersCounter], i, j);
                myLayout->setAlignment(blueCheckers[blueCheckersCounter], Qt::AlignCenter);
                blueCheckersCounter++;
            }
        }
    }
    setLayout(myLayout);
}

void GameBoard::paintEvent(QPaintEvent *)
{
    myLayout->setContentsMargins(window()->width() / 10, 0, window()->width() / 10, 0);
}

void GameBoard::mousePressEvent(QMouseEvent *)
{

}

bool GameBoard::getHasActiveChecker()
{
    return hasActiveChecker;
}

void GameBoard::setHasActiveChecker(bool f)
{
    hasActiveChecker = f;
}

Checker *GameBoard::getActiveChecker()
{
    for (int i = 0; i < blueCheckers.size(); ++i) {
        if (blueCheckers[i]->getIsClicked()) {
            return blueCheckers[i];
        }
    }
    return Q_NULLPTR;
}

QVector<Checker *> GameBoard::getCheckers()
{
    QVector<Checker *> checkers;
    for (int i = 0; i < redCheckers.size(); ++i) {
        checkers.push_back(redCheckers[i]);
    }
    for (int i = 0; i < blueCheckers.size(); ++i) {
        checkers.push_back(blueCheckers[i]);
    }
    return checkers;
}

QVector<QVector<Cell *> > GameBoard::getCells()
{
    return cells;
}

QGridLayout *GameBoard::getLayout()
{
    return myLayout;
}

void GameBoard::removeChecker(int iRemove, int jRemove)
{
    for (int i = 0; i < redCheckers.size(); ++i) {
        if (redCheckers[i]->getI() == iRemove && redCheckers[i]->getJ() == jRemove) {
            myLayout->removeWidget(redCheckers[i]);
            delete redCheckers[i];
            redCheckers.remove(i);
            break;
        }
    }
    for (int i = 0; i < blueCheckers.size(); ++i) {
        if (blueCheckers[i]->getI() == iRemove && blueCheckers[i]->getJ() == jRemove) {
            myLayout->removeWidget(blueCheckers[i]);
            delete blueCheckers[i];
            blueCheckers.remove(i);
            break;
        }
    }
}

void GameBoard::moveChecker(Checker *activeChecker, int iActive, int jActive)
{
    bool jumped = false;
    if (abs(activeChecker->getI() - iActive) == 2)
        jumped = true;
    myLayout->removeWidget(activeChecker);
    myLayout->addWidget(activeChecker, iActive, jActive);
    myLayout->setAlignment(activeChecker, Qt::AlignCenter);
    activeChecker->setI(iActive);
    activeChecker->setJ(jActive);
    if (activeChecker->getColor() == Qt::red && jumped) {
        ai::oneMoreJump(activeChecker);
    }
    if (activeChecker->getColor() == Qt::blue && jumped && activeChecker->canJump()) {
        for (int i = 0; i < blueCheckers.size(); ++i) {
            if (blueCheckers[i] != activeChecker) {
                blueCheckers[i]->setBlocked(true);
            }
        }
        activeChecker->setShouldJump(true);
    }
    else {
        for (int i = 0; i < blueCheckers.size(); ++i) {
            blueCheckers[i]->setCanMove(true);
        }
        activeChecker->setShouldJump(false);
        activeChecker->deactivate();
    }
}


