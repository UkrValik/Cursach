#include "ai.h"
#include "checker.h"
#include "cell.h"
#include "gameboard.h"
#include "game.h"

QVector<CheckerProtoMove *> ai::redMovableCheckers(QVector<CheckerProto *> checkers)
{
    QVector<CheckerProtoMove *> res;
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == Qt::red && !checkers[i]->killed) {
            for (int j = 0; j < 4; ++j) {
                int signX = qCos((j / 2) * M_PI);
                int signY = qCos(((j + 1) / 2) * M_PI);
                int cellX = checkers[i]->i + 2 * signX;
                int cellY = checkers[i]->j + 2 * signY;
                if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
                    bool canJump = false;
                    for (int k = 0; k < checkers.size(); ++k) {
                        if (checkers[k]->i == cellX && checkers[k]->j == cellY && !checkers[k]->killed) {
                            canJump = false;
                            break;
                        }
                        if (!checkers[k]->killed && checkers[k]->color == Qt::blue && (checkers[i]->i + cellX) / 2 == checkers[k]->i && (checkers[i]->j + cellY) / 2 == checkers[k]->j) {
                            canJump = true;
                        }
                    }
                    if (canJump) {
                        CheckerProtoMove *wannaMove = new CheckerProtoMove;
                        wannaMove->checker = checkers[i]->checker;
                        wannaMove->i = checkers[i]->i;
                        wannaMove->j = checkers[i]->j;
                        wannaMove->color = checkers[i]->color;
                        wannaMove->killed = checkers[i]->killed;
                        wannaMove->toI = cellX;
                        wannaMove->toJ = cellY;
                        res.push_back(wannaMove);
                    }
                }
            }
        }
    }
    if (!res.empty()) {
        return res;
    }
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == Qt::red && !checkers[i]->killed) {
            for (int j = 0; j < 2; ++j) {
                int cellX = checkers[i]->i + 1;
                int cellY = checkers[i]->j + qCos(((j + 1) / 2) * M_PI);
                if ((cellX >= 0 && cellX <= 7) && (cellY >= 0 && cellY <= 7)) {
                    bool canMove = true;
                    for (int k = 0; k < checkers.size(); ++k) {
                        if (checkers[k]->i == cellX && checkers[k]->j == cellY && !checkers[k]->killed) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        CheckerProtoMove *wannaMove = new CheckerProtoMove;
                        wannaMove->checker = checkers[i]->checker;
                        wannaMove->i = checkers[i]->i;
                        wannaMove->j = checkers[i]->j;
                        wannaMove->color = checkers[i]->color;
                        wannaMove->killed = checkers[i]->killed;
                        wannaMove->toI = cellX;
                        wannaMove->toJ = cellY;
                        res.push_back(wannaMove);
                    }
                }
            }
        }
    }
    return res;
}

QVector<CheckerProtoMove *> ai::blueMovableCheckers(QVector<CheckerProto *> checkers)
{
    QVector<CheckerProtoMove *> res;
    res.clear();
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == Qt::blue && !checkers[i]->killed) {
            for (int j = 0; j < 4; ++j) {
                int signX = qCos((j / 2) * M_PI);
                int signY = qCos(((j + 1) / 2) * M_PI);
                int cellX = checkers[i]->i + 2 * signX;
                int cellY = checkers[i]->j + 2 * signY;
                if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
                    bool canJump = false;
                    for (int k = 0; k < checkers.size(); ++k) {
                        if (checkers[k]->i == cellX && checkers[k]->j == cellY && !checkers[k]->killed) {
                            canJump = false;
                            break;
                        }
                        if (!checkers[k]->killed && checkers[k]->color == Qt::red && (checkers[i]->i + cellX) / 2 == checkers[k]->i && (checkers[i]->j + cellY) / 2 == checkers[k]->j) {
                            canJump = true;
                        }
                    }
                    if (canJump) {
                        CheckerProtoMove *wannaMove = new CheckerProtoMove;
                        wannaMove->checker = checkers[i]->checker;
                        wannaMove->i = checkers[i]->i;
                        wannaMove->j = checkers[i]->j;
                        wannaMove->color = checkers[i]->color;
                        wannaMove->killed = checkers[i]->killed;
                        wannaMove->toI = cellX;
                        wannaMove->toJ = cellY;
                        res.push_back(wannaMove);
                    }
                }
            }
        }
    }
    if (!res.empty()) {
        return res;
    }
    for (int i = 0; i < checkers.size(); ++i) {
        if (checkers[i]->color == Qt::blue && !checkers[i]->killed) {
            for (int j = 0; j < 2; ++j) {
                int cellX = checkers[i]->i - 1;
                int cellY = checkers[i]->j + qCos(((j + 1) / 2) * M_PI);
                if ((cellX >= 0 && cellX <= 7) && (cellY >= 0 && cellY <= 7)) {
                    bool canMove = true;
                    for (int k = 0; k < checkers.size(); ++k) {
                        if (checkers[k]->i == cellX && checkers[k]->j == cellY && !checkers[k]->killed) {
                            canMove = false;
                            break;
                        }
                    }
                    if (canMove) {
                        CheckerProtoMove *wannaMove = new CheckerProtoMove;
                        wannaMove->checker = checkers[i]->checker;
                        wannaMove->i = checkers[i]->i;
                        wannaMove->j = checkers[i]->j;
                        wannaMove->color = checkers[i]->color;
                        wannaMove->killed = checkers[i]->killed;
                        wannaMove->toI = cellX;
                        wannaMove->toJ = cellY;
                        res.push_back(wannaMove);
                    }
                }
            }
        }
    }
    return res;
}

QVector<CheckerProtoMove *> ai::redOneMoreJump(QVector<CheckerProto *> checkers, int jumped)
{
    QVector<CheckerProtoMove *> res;
    for (int i = 0; i < 4; ++i) {
        int signX = qCos((i / 2) * M_PI);
        int signY = qCos(((i + 1) / 2) * M_PI);
        int cellX = checkers[jumped]->i + 2 * signX;
        int cellY = checkers[jumped]->j + 2 * signY;
        if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
            bool canJump = false;
            for (int k = 0; k < checkers.size(); ++k) {
                if (checkers[k]->i == cellX && checkers[k]->j == cellY && !checkers[k]->killed) {
                    canJump = false;
                    break;
                }
                if (!checkers[k]->killed && checkers[k]->color != checkers[jumped]->color && (checkers[jumped]->i + cellX) / 2 == checkers[k]->i && (checkers[jumped]->j + cellY) / 2 == checkers[k]->j) {
                    canJump = true;
                }
                if (canJump) {
                    CheckerProtoMove *wannaMove = new CheckerProtoMove;
                    wannaMove->checker = checkers[jumped]->checker;
                    wannaMove->i = checkers[jumped]->i;
                    wannaMove->j = checkers[jumped]->j;
                    wannaMove->color = checkers[jumped]->color;
                    wannaMove->killed = checkers[jumped]->killed;
                    wannaMove->toI = cellX;
                    wannaMove->toJ = cellY;
                    res.push_back(wannaMove);
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

void ai::smartMove(int depth, QVector<CheckerProto *> currentCheckersState, int currChecker)
{
    if (depth > 0) {
        QVector<CheckerProtoMove *> redMoves = redMovableCheckers(currentCheckersState);
        for (int i = 0; i < redMoves.size(); ++i) {
            if (currChecker == -1)
                currChecker = redMoves[i]->checker;
            currentCheckersState[redMoves[i]->checker]->i = redMoves[i]->toI;
            currentCheckersState[redMoves[i]->checker]->j = redMoves[i]->toJ;
            if (abs(redMoves[i]->i - redMoves[i]->toI) == 2) {
                int jumpedOverI = (redMoves[i]->i + redMoves[i]->toI) / 2;
                int jumpedOverJ = (redMoves[i]->j + redMoves[i]->toJ) / 2;
                int jumpedOver;
                for (int j = 0; j < currentCheckersState.size(); ++j) {
                    if (currentCheckersState[j]->i == jumpedOverI && currentCheckersState[j]->j == jumpedOverJ) {
                        jumpedOver = j;
                        break;
                    }
                }
                currentCheckersState[jumpedOver]->killed = true;
                currentCheckersState[currChecker]->profit++;
//                QVector<CheckerProtoMove *> redAddJumps = redOneMoreJump(currentCheckersState, i);
//                while(!redAddJumps.empty()) {
//                    for (int j = 0; j < redAddJumps.size(); ++j) {
//                        if (j == 0) {
//                            currentCheckersState[redAddJumps[j]->checker]->i = redAddJumps[j]->toI;
//                            currentCheckersState[redAddJumps[j]->checker]->j = redAddJumps[j]->toJ;
//                            int jumpedOverI = (redAddJumps[j]->i + redAddJumps[j]->toI) / 2;
//                            int jumpedOverJ = (redAddJumps[j]->j + redAddJumps[j]->toJ) / 2;
//                            int jumpedOver;
//                            for (int k = 0; k < currentCheckersState.size(); ++k) {
//                                if (currentCheckersState[k]->i == jumpedOverI && currentCheckersState[k]->j == jumpedOverJ) {
//                                    jumpedOver = j;
//                                    break;
//                                }
//                            }
//                            currentCheckersState[jumpedOver]->killed = true;
//                            currentCheckersState[currChecker]->profit++;
//                        }
//                        else {
//                            redMoves.push_back(redAddJumps[j]);
//                        }
//                    }
//                    redAddJumps = redOneMoreJump(currentCheckersState, redMoves[i]->checker);
//                }
            }
            QVector<CheckerProtoMove *> blueMoves = blueMovableCheckers(currentCheckersState);
            qDebug() << blueMoves.size() << redMoves.size() << redMoves[i]->i << redMoves[i]->j << redMoves[i]->toI << redMoves[i]->toJ;
            for (int j = 0; j < blueMoves.size(); ++j) {
                currentCheckersState[blueMoves[j]->checker]->i = blueMoves[j]->toI;
                currentCheckersState[blueMoves[j]->checker]->j = blueMoves[j]->toJ;
                if (abs(blueMoves[j]->i - blueMoves[j]->toI) == 2) {
                    int jumpedOverI = (blueMoves[j]->i + blueMoves[j]->toI) / 2;
                    int jumpedOverJ = (blueMoves[j]->j + blueMoves[j]->toJ) / 2;
                    int jumpedOver;
                    for (int k = 0; k < currentCheckersState.size(); ++k) {
                        if (currentCheckersState[k]->i == jumpedOverI && currentCheckersState[k]->j == jumpedOverJ) {
                            jumpedOver = k;
                            break;
                        }
                    }
                    currentCheckersState[jumpedOver]->killed = true;
                    currentCheckersState[currChecker]->profit--;
//                    QVector<CheckerProtoMove *> blueAddJumps = redOneMoreJump(currentCheckersState, j);
//                    while(!blueAddJumps.empty()) {
//                        //qDebug() << blueAddJumps.size();
//                        for (int k = 0; k < blueAddJumps.size(); ++k) {
//                            if (k == 0) {
//                                currentCheckersState[blueAddJumps[k]->checker]->i = blueAddJumps[k]->toI;
//                                currentCheckersState[blueAddJumps[k]->checker]->j = blueAddJumps[k]->toJ;
//                                int jumpedOverI = (blueAddJumps[k]->i + blueAddJumps[k]->toI) / 2;
//                                int jumpedOverJ = (blueAddJumps[k]->j + blueAddJumps[k]->toJ) / 2;
//                                int jumpedOver;
//                                for (int p = 0; p < currentCheckersState.size(); ++p) {
//                                    if (currentCheckersState[p]->i == jumpedOverI && currentCheckersState[p]->j == jumpedOverJ) {
//                                        jumpedOver = p;
//                                        break;
//                                    }
//                                }
//                                currentCheckersState[jumpedOver]->killed = true;
//                                currentCheckersState[currChecker]->profit--;
//                            }
//                            else {
//                                blueMoves.push_back(blueAddJumps[k]);
//                            }
//                        }
//                        blueAddJumps = redOneMoreJump(currentCheckersState, blueMoves[j]->checker);
//                    }
                }
                smartMove(depth - 1, currentCheckersState, i);
                currentCheckersState[blueMoves[j]->checker]->i = blueMoves[j]->i;
                currentCheckersState[blueMoves[j]->checker]->j = blueMoves[j]->j;
            }
            currentCheckersState[redMoves[i]->checker]->i = redMoves[i]->i;
            currentCheckersState[redMoves[i]->checker]->j = redMoves[i]->j;
        }
    }
}

void ai::makeSmartMove()
{
    GameBoard *gb = game->getGB();
    QVector<Checker *> checkers = gb->getCheckers();
    QVector<CheckerProto *> complexCheckers(checkers.size());
    for (int i = 0; i < checkers.size(); ++i) {
        complexCheckers[i] = new CheckerProto;
        complexCheckers[i]->checker = i;
        complexCheckers[i]->color = checkers[i]->getColor();
        complexCheckers[i]->i = checkers[i]->getI();
        complexCheckers[i]->j = checkers[i]->getJ();
        complexCheckers[i]->killed = false;
        complexCheckers[i]->profit = 0;
    }
    smartMove(1, complexCheckers, -1);
    QVector<int> profits;
    for (int i = 0; i < complexCheckers.size(); ++i) {
        profits.push_back(complexCheckers[i]->profit);
    }
    qDebug() << profits;
}
