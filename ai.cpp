#include "ai.h"
#include "checker.h"
#include "cell.h"
#include "gameboard.h"
#include "game.h"

QVector<QPoint> ai::canJump(QVector<CheckerProto *> checkers, QColor color, CheckerProto *currChecker, CheckerProto *jumpedOver)
{
    QVector<QPoint> res;
    for (int j = 0; j < 4; ++j) {
        int signX = qCos((j / 2) * M_PI);
        int signY = qCos(((j + 1) / 2) * M_PI);
        int cellX = currChecker->cell.x() + 2 * signX;
        int cellY = currChecker->cell.y() + 2 * signY;
        if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
            bool canJump = false;
            for (int k = 0; k < checkers.size(); ++k) {
                if (checkers[k]->cell.x() == cellX && checkers[k]->cell.y() == cellY && !checkers[k]->killed) {
                    canJump = false;
                    break;
                }
                if (!checkers[k]->killed
                  && checkers[k]->color != color
                  && (currChecker->cell.x() + cellX) / 2 == checkers[k]->cell.x()
                  && (currChecker->cell.y() + cellY) / 2 == checkers[k]->cell.y()
                  && checkers[k] != jumpedOver) {
                    canJump = true;
                }
            }
            if (canJump) res.push_back(QPoint(cellX, cellY));
        }
    }
    return res;
}

QVector<QVector<QPoint> > ai::jumpWays(QVector<CheckerProto *> checkers, QColor color, CheckerProto *currChecker)
{
    QVector<QVector<QPoint> > res;
    QVector<QPoint> firstJump = canJump(checkers, color, currChecker, Q_NULLPTR);
    if (firstJump.empty()) return res;
    for (int i = 0; i < firstJump.size(); ++i) {
        CheckerProto *jumpedOver = new CheckerProto, *newCurrChecker = new CheckerProto;
        for (int j = 0; j < checkers.size(); ++j) {
            if ((currChecker->cell.x() + firstJump[i].x()) / 2 == checkers[j]->cell.x()
                && (currChecker->cell.y() + firstJump[i].y()) / 2 == checkers[j]->cell.y()) {
                jumpedOver->cell = checkers[j]->cell;
                jumpedOver->checker = checkers[j]->checker;
                jumpedOver->color = checkers[j]->color;
                jumpedOver->killed = checkers[j]->killed;
                jumpedOver->profit = checkers[j]->profit;
            }
            if (checkers[j]->cell.x() == currChecker->cell.x() && checkers[j]->cell.y() == currChecker->cell.y()) {
                newCurrChecker->cell = checkers[j]->cell;
                newCurrChecker->checker = checkers[j]->checker;
                newCurrChecker->color = checkers[j]->color;
                newCurrChecker->killed = checkers[j]->killed;
                newCurrChecker->profit = checkers[j]->profit;
            }
        }
        newCurrChecker->cell = firstJump[i];
        QVector<QPoint> secondJump = canJump(checkers, color, newCurrChecker, jumpedOver);
        if (secondJump.empty()) {
            QVector<QPoint> way;
            way.push_back(firstJump[i]);
            res.push_back(way);
        }


        for (int i2 = 0; i2 < secondJump.size(); ++i2) {
            CheckerProto *jumpedOver2 = new CheckerProto, *newCurrChecker2 = new CheckerProto;
            for (int j = 0; j < checkers.size(); ++j) {
                if ((newCurrChecker->cell.x() + secondJump[i2].x()) / 2 == checkers[j]->cell.x()
                    && (newCurrChecker->cell.y() + secondJump[i2].y()) / 2 == checkers[j]->cell.y()) {
                    jumpedOver2->cell = checkers[j]->cell;
                    jumpedOver2->checker = checkers[j]->checker;
                    jumpedOver2->color = checkers[j]->color;
                    jumpedOver2->killed = checkers[j]->killed;
                    jumpedOver2->profit = checkers[j]->profit;
                }
                if (checkers[j]->cell.x() == newCurrChecker->cell.x() && checkers[j]->cell.y() == newCurrChecker->cell.y()) {
                    newCurrChecker2->cell = checkers[j]->cell;
                    newCurrChecker2->checker = checkers[j]->checker;
                    newCurrChecker2->color = checkers[j]->color;
                    newCurrChecker2->killed = checkers[j]->killed;
                    newCurrChecker2->profit = checkers[j]->profit;
                }
            }
            newCurrChecker2->cell = secondJump[i2];
            QVector<QPoint> thirdJump = canJump(checkers, color, newCurrChecker2, jumpedOver2);
            if (thirdJump.empty()) {
                QVector<QPoint> way;
                way.push_back(firstJump[i]);
                way.push_back(secondJump[i2]);
                res.push_back(way);
            }


            for (int i3 = 0; i3 < thirdJump.size(); ++i3) {
                CheckerProto *jumpedOver3 = new CheckerProto, *newCurrChecker3 = new CheckerProto;
                for (int j = 0; j < checkers.size(); ++j) {
                    if ((newCurrChecker2->cell.x() + thirdJump[i3].x()) / 2 == checkers[j]->cell.x()
                        && (newCurrChecker2->cell.y() + thirdJump[i3].y()) / 2 == checkers[j]->cell.y()) {
                        jumpedOver3->cell = checkers[j]->cell;
                        jumpedOver3->checker = checkers[j]->checker;
                        jumpedOver3->color = checkers[j]->color;
                        jumpedOver3->killed = checkers[j]->killed;
                        jumpedOver3->profit = checkers[j]->profit;
                    }
                    if (checkers[j]->cell.x() == newCurrChecker2->cell.x() && checkers[j]->cell.y() == newCurrChecker2->cell.y()) {
                        newCurrChecker3->cell = checkers[j]->cell;
                        newCurrChecker3->checker = checkers[j]->checker;
                        newCurrChecker3->color = checkers[j]->color;
                        newCurrChecker3->killed = checkers[j]->killed;
                        newCurrChecker3->profit = checkers[j]->profit;
                    }
                }
                newCurrChecker3->cell = thirdJump[i3];
                QVector<QPoint> forthJump = canJump(checkers, color, newCurrChecker3, jumpedOver3);
                if (forthJump.empty()) {
                    QVector<QPoint> way;
                    way.push_back(firstJump[i]);
                    way.push_back(secondJump[i2]);
                    way.push_back(thirdJump[i3]);
                    res.push_back(way);
                }
                else {
                    for (int i4 = 0; i4 < forthJump.size(); ++i4) {
                        QVector<QPoint> way;
                        way.push_back(firstJump[i]);
                        way.push_back(secondJump[i2]);
                        way.push_back(thirdJump[i3]);
                        way.push_back(forthJump[i4]);
                        res.push_back(way);
                    }
                }
            }
        }
    }
    return res;
}

QVector<CheckerProtoMove *> ai::movableCheckers(QVector<CheckerProto *> checkers, QColor color)
{
    QVector<CheckerProtoMove *> res;
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == color && !checkers[i]->killed) {
            QVector<QVector<QPoint> > jumps = jumpWays(checkers, color, checkers[i]);
            for (int j = 0; j < jumps.size(); ++j) {
                CheckerProtoMove *wannaMove = new CheckerProtoMove;
                wannaMove->checker = checkers[i]->checker;
                wannaMove->color = color;
                wannaMove->from = checkers[i]->cell;
                wannaMove->killed = checkers[i]->killed;
                wannaMove->to = jumps[j];
                wannaMove->kills = wannaMove->to.size();
                res.push_back(wannaMove);
            }
        }
    }
    if (!res.empty()) {
        return res;
    }
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == color && !checkers[i]->killed) {
            for (int j = 0; j < 2; ++j) {
                int cellX = -1;
                if (color == Qt::red)
                    cellX = checkers[i]->cell.x() + 1;
                else
                    cellX = checkers[i]->cell.x() - 1;
                int cellY = checkers[i]->cell.y() + qCos(((j + 1) / 2) * M_PI);
                if ((cellX >= 0 && cellX <= 7) && (cellY >= 0 && cellY <= 7)) {
                    bool canMove = true;
                    for (int k = 0; k < checkers.size(); ++k) {
                        if (checkers[k]->cell.x() == cellX
                                && checkers[k]->cell.y() == cellY
                                && !checkers[k]->killed) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        CheckerProtoMove *wannaMove = new CheckerProtoMove;
                        wannaMove->checker = checkers[i]->checker;
                        wannaMove->from.setX(checkers[i]->cell.x());
                        wannaMove->from.setY(checkers[i]->cell.y());
                        wannaMove->color = checkers[i]->color;
                        wannaMove->killed = checkers[i]->killed;
                        wannaMove->to.push_back(QPoint(cellX, cellY));
                        wannaMove->kills = 0;
                        res.push_back(wannaMove);
                    }
                }
            }
        }
    }
    return res;
}

ai::ai()
{

}

void ai::makeRandomMove()
{
    struct CheckerIJ {
        Checker *check;
        int i, j;
    };
    GameBoard *gb = game->getGB();
    QVector<QVector<Cell *> > cells = gb->getCells();
    QVector<Checker *> checkers = gb->getCheckers();
    QVector<CheckerIJ *> movableCheckers;
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->getColor() == Qt::red) {
            for (int j = 0; j < 4; ++j) {
                int signX = qCos((j / 2) * M_PI);
                int signY = qCos(((j + 1) / 2) * M_PI);
                int cellX = (checkers[i]->getI() + 2 * signX);
                int cellY = (checkers[i]->getJ() + 2 * signY);
                if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
                    if (cells[cellX][cellY]->mayJump(checkers, checkers[i]->getI(), checkers[i]->getJ(), checkers[i]->getColor())) {
                        CheckerIJ *wannaMove = new CheckerIJ;
                        wannaMove->check = checkers[i];
                        wannaMove->i = cellX;
                        wannaMove->j = cellY;
                        movableCheckers.push_back(wannaMove);
                    }
                }
            }
        }
    }
    if (movableCheckers.isEmpty()) {
        for (int i = 0; i < checkers.size(); ++i) {
            if (checkers[i]->getColor() == Qt::red) {
                for (int j = 0; j < 2; ++j) {
                    int cellX = checkers[i]->getI() + 1;
                    int cellY = checkers[i]->getJ() + qCos(((j + 1) / 2) * M_PI);
                    if ((cellX >= 0 && cellX <= 7) && (cellY >= 0 && cellY <= 7)) {
                        if (cells[cellX][cellY]->mayMove(checkers, checkers[i]->getI(), checkers[i]->getJ())) {
                            CheckerIJ *wannaMove = new CheckerIJ;
                            wannaMove->check = checkers[i];
                            wannaMove->i = cellX;
                            wannaMove->j = cellY;
                            movableCheckers.push_back(wannaMove);
                        }
                    }
                }
            }
        }
    }
    if (!movableCheckers.empty()) {
        int nChecker = QRandomGenerator::global()->bounded(movableCheckers.size());
        CheckerIJ *wannaMove = movableCheckers[nChecker];
        //game->delay(2);
        wannaMove->check->activate();
        game->delay(1);
        for (int i = 0; i < checkers.size(); ++i) {
            if (abs(wannaMove->check->getI() - wannaMove->i) == 2 && abs(wannaMove->check->getJ() - wannaMove->j) == 2) {
                gb->removeChecker((wannaMove->check->getI() + wannaMove->i) / 2, (wannaMove->check->getJ() + wannaMove->j) / 2);
                break;
            }
        }
        gb->moveChecker(wannaMove->check, wannaMove->i, wannaMove->j);
        for (int i = 0; i < cells.size(); ++i) {
            for (int j = 0; j < cells[i].size(); ++j) {
                cells[i][j]->lower();
            }
        }
        checkers = gb->getCheckers();
        for (int i = 0; i < checkers.size(); ++i) {
            checkers[i]->setBlocked(false);
        }
    }
}

void ai::oneMoreJump(Checker *activeChecker)
{
    activeChecker->activate();
    game->delay(1);
    struct CheckerIJ {
        Checker *check;
        int i, j;
    };
    GameBoard *gb = game->getGB();
    QVector<QVector<Cell *> > cells = gb->getCells();
    QVector<Checker *> checkers = gb->getCheckers();
    QVector<CheckerIJ *> movableCheckers;
    for (int j = 0; j < 4; ++j) {
        int signX = qCos((j / 2) * M_PI);
        int signY = qCos(((j + 1) / 2) * M_PI);
        int cellX = (activeChecker->getI() + 2 * signX);
        int cellY = (activeChecker->getJ() + 2 * signY);
        if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
            if (cells[cellX][cellY]->mayJump(checkers, activeChecker->getI(), activeChecker->getJ(), activeChecker->getColor())) {
                CheckerIJ *wannaMove = new CheckerIJ;
                wannaMove->check = activeChecker;
                wannaMove->i = cellX;
                wannaMove->j = cellY;
                movableCheckers.push_back(wannaMove);
            }
        }
    }
    if (!movableCheckers.empty()) {
        int nChecker = QRandomGenerator::global()->bounded(movableCheckers.size());
        CheckerIJ *wannaMove = movableCheckers[nChecker];
        for (int i = 0; i < checkers.size(); ++i) {
            if (abs(wannaMove->check->getI() - wannaMove->i) == 2 && abs(wannaMove->check->getJ() - wannaMove->j) == 2) {
                gb->removeChecker((wannaMove->check->getI() + wannaMove->i) / 2, (wannaMove->check->getJ() + wannaMove->j) / 2);
                break;
            }
        }
        gb->moveChecker(wannaMove->check, wannaMove->i, wannaMove->j);
        for (int i = 0; i < cells.size(); ++i) {
            for (int j = 0; j < cells[i].size(); ++j) {
                cells[i][j]->lower();
            }
        }
    }
    activeChecker->deactivate();
}

void ai::smartMove(int level, int depth, QVector<CheckerProto *> currentCheckersState, int currChecker, int *profitsAttack, int *profitsDefend, QVector<QPoint> *bestAttackMoves, QVector<QPoint> *bestDefendMoves, QVector<QPoint> bestOne)
{
    if (level > 0) {
        QVector<CheckerProtoMove *> redMoves = movableCheckers(currentCheckersState, Qt::red);
        for (int i = 0; i < redMoves.size(); ++i) {
            if (level == depth) {
                currChecker = redMoves[i]->checker;
                bestOne = redMoves[i]->to;
            }

            QVector<CheckerProto *> nextCheckersState;
            for (int j = 0; j < currentCheckersState.size(); ++j) {
                CheckerProto *temp = new CheckerProto;
                temp->cell = currentCheckersState[j]->cell;
                temp->checker = currentCheckersState[j]->checker;
                temp->color = currentCheckersState[j]->color;
                temp->killed = currentCheckersState[j]->killed;
                temp->profit = currentCheckersState[j]->profit;
                nextCheckersState.push_back(temp);
            }
            if (redMoves[i]->kills > 0) {
                for (int j = 0; j < redMoves[i]->kills; ++j) {
                    int death = -1;
                    for (int k = 0; k < nextCheckersState.size(); ++k) {
                        if (j == 0) {
                            if (nextCheckersState[k]->cell.x() == (nextCheckersState[redMoves[i]->checker]->cell.x() + redMoves[i]->to[j].x()) / 2
                                    && nextCheckersState[k]->cell.y() == (nextCheckersState[redMoves[i]->checker]->cell.y() + redMoves[i]->to[j].y()) / 2) {
                                death = k;
                                break;
                            }
                        }
                        else {
                            if (nextCheckersState[k]->cell.x() == (redMoves[i]->to[j].x() + redMoves[i]->to[j - 1].x()) / 2
                                    && nextCheckersState[k]->cell.y() == (redMoves[i]->to[j].y() + redMoves[i]->to[j - 1].y()) / 2) {
                                death = k;
                                break;
                            }
                        }
                    }
                    nextCheckersState[death]->killed = true;
                }
                nextCheckersState[redMoves[i]->checker]->cell = redMoves[i]->to[redMoves[i]->kills - 1];
            }
            else {
                nextCheckersState[redMoves[i]->checker]->cell = redMoves[i]->to[0];
            }

            QVector<CheckerProtoMove *> blueMoves = movableCheckers(nextCheckersState, Qt::blue);
            for (int j = 0; j < blueMoves.size(); ++j) {
                QVector<CheckerProto *> checkersStateBlueMove;
                for (int k = 0; k < nextCheckersState.size(); ++k) {
                    CheckerProto *temp = new CheckerProto;
                    temp->cell = nextCheckersState[k]->cell;
                    temp->checker = nextCheckersState[k]->checker;
                    temp->color = nextCheckersState[k]->color;
                    temp->killed = nextCheckersState[k]->killed;
                    temp->profit = nextCheckersState[k]->profit;
                    checkersStateBlueMove.push_back(temp);
                }
                if (blueMoves[j]->kills > 0) {
                    for (int j1 = 0; j1 < blueMoves[j]->kills; ++j1) {
                        int death = -1;
                        for (int k = 0; k < checkersStateBlueMove.size(); ++k) {
                            if (j1 == 0) {
                                if (checkersStateBlueMove[k]->cell.x() == (checkersStateBlueMove[blueMoves[j]->checker]->cell.x() + blueMoves[j]->to[j1].x()) / 2
                                        && checkersStateBlueMove[k]->cell.y() == (checkersStateBlueMove[blueMoves[j]->checker]->cell.y() + blueMoves[j]->to[j1].y()) / 2) {
                                    death = k;
                                    break;
                                }
                            }
                            else {
                                if (checkersStateBlueMove[k]->cell.x() == (blueMoves[j]->to[j1].x() + blueMoves[j]->to[j1 - 1].x()) / 2
                                        && checkersStateBlueMove[k]->cell.y() == (blueMoves[j]->to[j1].y() + blueMoves[j]->to[j1 - 1].y()) / 2) {
                                    death = k;
                                    break;
                                }
                            }
                        }
                        checkersStateBlueMove[death]->killed = true;
                    }
                    checkersStateBlueMove[blueMoves[j]->checker]->cell = blueMoves[j]->to[blueMoves[j]->kills - 1];
                }
                else {
                    checkersStateBlueMove[blueMoves[j]->checker]->cell = blueMoves[j]->to[0];
                }

                smartMove(level - 1, depth, checkersStateBlueMove, currChecker, profitsAttack, profitsDefend, bestAttackMoves, bestDefendMoves, bestOne);
                currentCheckersState[currChecker]->profit = checkersStateBlueMove[currChecker]->profit;
                for (int k = 0; k < checkersStateBlueMove.size(); ++k) {
                    delete checkersStateBlueMove[k];
                }
                delete blueMoves[j];
            }
            for (int j = 0; j < nextCheckersState.size(); ++j) {
                delete nextCheckersState[j];
            }
            delete redMoves[i];
        }
    }
    else {
        int profit = 0;
        for (int i = 0; i < currentCheckersState.size(); ++i) {
            if (currentCheckersState[i]->killed && currentCheckersState[i]->color == Qt::red)
                profit--;
            if (currentCheckersState[i]->killed && currentCheckersState[i]->color == Qt::blue)
                profit++;
        }
        bestAttackMoves[currChecker] = bestOne;
        bestDefendMoves[currChecker] = bestOne;
        if (profitsAttack[currChecker] < profit) {
            profitsAttack[currChecker] = profit;
            bestAttackMoves[currChecker] = bestOne;
        }
        if (profitsDefend[currChecker] > profit) {
            profitsDefend[currChecker] = profit;
            bestDefendMoves[currChecker] = bestOne;
        }
    }
}

void ai::makeSmartMove()
{
    GameBoard *gb = game->getGB();
    QVector<Checker *> checkers = gb->getCheckers();
    QVector<QVector<Cell *> > cells = gb->getCells();
    QVector<CheckerProto *> complexCheckers(checkers.size());
    for (int i = 0; i < checkers.size(); ++i) {
        complexCheckers[i] = new CheckerProto;
        complexCheckers[i]->checker = i;
        complexCheckers[i]->color = checkers[i]->getColor();
        complexCheckers[i]->cell.setX(checkers[i]->getI());
        complexCheckers[i]->cell.setY(checkers[i]->getJ());
        complexCheckers[i]->killed = false;
        complexCheckers[i]->profit = 0;
    }
    int *profitsAttack = new int[complexCheckers.size()], *profitsDefend = new int[complexCheckers.size()];
    for (int i = 0; i < complexCheckers.size(); ++i) {
        profitsAttack[i] = 0;
        profitsDefend[i] = 0;
    }
    QVector<QPoint> *bestAttackMoves = new QVector<QPoint>[complexCheckers.size()],
            *bestDefendMoves = new QVector<QPoint>[complexCheckers.size()];
    QVector<QPoint> bestOne;
    smartMove(2, 2, complexCheckers, -1, profitsAttack, profitsDefend, bestAttackMoves, bestDefendMoves, bestOne);
    int bestProfit = -5;
    for (int i = 0; i < complexCheckers.size(); ++i) {
        if (bestProfit < profitsAttack[i] + profitsDefend[i] && !bestAttackMoves[i].empty())
            bestProfit = profitsAttack[i] + profitsDefend[i];
        qDebug() << profitsAttack[i] << profitsDefend[i] << i << bestAttackMoves[i] << bestDefendMoves[i];
    }
    QVector<int> bestMoves;
    for (int i = 0; i < complexCheckers.size(); ++i) {
        if (bestProfit == profitsAttack[i] + profitsDefend[i] && !bestAttackMoves[i].empty()) {
            bestMoves.push_back(i);
        }
    }
    qDebug() << "bestProfit" << bestProfit;
    qDebug() << "bestMovesSize" << bestMoves.size();
    if (bestMoves.size() > 0) {
        int nChecker = QRandomGenerator::global()->bounded(bestMoves.size());
        nChecker = bestMoves[nChecker];
        checkers[nChecker]->activate();
        qDebug() << nChecker;
        game->delay(1);
        if (abs(checkers[nChecker]->getI() - bestAttackMoves[nChecker][0].x()) == 2) {
            qDebug() << (checkers[nChecker]->getI() + bestAttackMoves[nChecker][0].x()) / 2 << (checkers[nChecker]->getJ() + bestAttackMoves[nChecker][0].y()) / 2;
            gb->removeChecker((checkers[nChecker]->getI() + bestAttackMoves[nChecker][0].x()) / 2, (checkers[nChecker]->getJ() + bestAttackMoves[nChecker][0].y()) / 2);
        }
        gb->moveChecker(checkers[nChecker], bestAttackMoves[nChecker][0].x(), bestAttackMoves[nChecker][0].y());

        for (int i = 0; i < cells.size(); ++i) {
            for (int j = 0; j < cells[i].size(); ++j) {
                cells[i][j]->lower();
            }
        }

        checkers = gb->getCheckers();
        for (int i = 0; i < checkers.size(); ++i) {
            checkers[i]->setBlocked(false);
        }
    }

    for (int i = 0; i < complexCheckers.size(); ++i) {
        delete complexCheckers[i];
    }
    delete[] profitsAttack;
    delete[] profitsDefend;
}
