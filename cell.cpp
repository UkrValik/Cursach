#include "cell.h"
#include "gameboard.h"
#include "game.h"
#include "checker.h"
#include "ai.h"

bool Cell::mayMove(QVector<Checker *> checkers, int iActive, int jActive)
{
    Checker *wannaMove;
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->getI() == iGrid && checkers[i]->getJ() == jGrid) {
            return false;
        }
        if (checkers[i]->getI() == iActive && checkers[i]->getJ() == jActive) {
            wannaMove = checkers[i];
        }
    }
    if (wannaMove->getColor() == Qt::blue) {
        if (!((jActive - 1 == jGrid || jActive + 1 == jGrid) && iActive - 1 == iGrid))
            return false;
    }
    if (wannaMove->getColor() == Qt::red) {
        if (!((jActive - 1 == jGrid || jActive + 1 == jGrid) && iActive + 1 == iGrid))
            return false;
    }
    return true;
}

bool Cell::mayJump(QVector<Checker *> checkers, int iActive, int jActive, QColor activeColor)
{
    bool jumpOver = false;
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->getI() == iGrid && checkers[i]->getJ() == jGrid)
            return false;
        if ((iActive + iGrid) / 2 == checkers[i]->getI() && (jActive + jGrid) / 2 == checkers[i]->getJ() && checkers[i]->getColor() != activeColor) {
            jumpOver = true;
        }
    }
    if (!(abs(jActive - jGrid) == 2 && abs(iActive - iGrid) == 2)) {
        return false;
    }
    return jumpOver;
}
Game *game;
void Cell::aiMove()
{
    QVector<Checker *> checkers = game->getGB()->getCheckers();
    for (int i = 0; i < checkers.size(); ++i) {
        checkers[i]->setBlocked(true);
    }
    ai::makeSmartMove();
    ai::makeRandomMove();
}

Cell::Cell(QColor color, int iGrid, int jGrid, QWidget *)
{
    setFixedSize(window()->width() / 10, window()->height() / 10);
    this->color = color;
    this->iGrid = iGrid;
    this->jGrid = jGrid;
}

void Cell::paintEvent(QPaintEvent *)
{
    setFixedSize(window()->width() / 10, window()->height() / 8);
    QPainter painter(this);
    painter.fillRect(rect(), color);
    painter.end();
}

void Cell::mousePressEvent(QMouseEvent *)
{
    GameBoard *gm = qobject_cast<GameBoard*>(this->parent());
    if (gm->getHasActiveChecker()) {
        QList<QObject*> gmChildren = gm->children();
        QVector<Checker*> checkers;
        QVector<Cell*> cells;
        for (int i = 1; i < gmChildren.size(); ++i) {
            Checker *ch = qobject_cast<Checker*>(gmChildren.at(i));
            Cell *ce = qobject_cast<Cell*>(gmChildren.at(i));
            if (ch) checkers.push_back(ch);
            if (ce) cells.push_back(ce);
        }
        int iActive, jActive;
        Checker *activeChecker;
        bool canMove = true;
        for (int i = 0; i < checkers.size(); ++i) {
            if (checkers[i]->getIsClicked()) {
                iActive = checkers[i]->getI();
                jActive = checkers[i]->getJ();
                activeChecker = checkers[i];
            }
            if (checkers[i]->canJump() && checkers[i]->getColor() == Qt::blue)
                canMove = false;
        }
        if (!canMove) {
            for (int i = 0; i < checkers.size(); ++i) {
                if (checkers[i]->getColor() == Qt::blue)
                    checkers[i]->setCanMove(false);
            }
        }
        if (mayMove(checkers, iActive, jActive) && !activeChecker->getShouldJump() && activeChecker->getCanMove()) {
            emit moveThisChecker(activeChecker, iGrid, jGrid);
            if (!game->getGB()->getHasActiveChecker()) {
                aiMove();
            }
        }
        if (mayJump(checkers, iActive, jActive, activeChecker->getColor())) {
            game->getGB()->removeChecker((iActive + iGrid) / 2, (jActive + jGrid) / 2);
            emit moveThisChecker(activeChecker, iGrid, jGrid);
            if (!game->getGB()->getHasActiveChecker()) {
                aiMove();
            }
        }
    }
}

QColor Cell::getColor()
{
    return color;
}

bool Cell::hasChecker()
{
    GameBoard *gb = game->getGB();
    QVector<Checker *> checkers = gb->getCheckers();
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->getI() == iGrid && checkers[i]->getJ() == jGrid)
            return true;
    }
    return false;
}
