#pragma once
#include <QtWidgets>
//#include "gameboard.h"

class Checker : public QWidget
{
    Q_OBJECT
private:
    int iGrid, jGrid;
    QColor color;
    bool isClicked;
    bool blocked;
    bool isQueen;
    bool shouldJump;
    bool canMove;

    void drawChecker();
    void drawActiveChecker();
    void drawQueen();
    void drawActiveQueen();
public:
    Checker(int, int, QColor, QWidget *pwgt = 0);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

    bool getIsClicked();
    int getI();
    int getJ();
    void setI(int i);
    void setJ(int j);
    QColor getColor();
    void activate();
    void deactivate();
    bool getBlocked();
    void setBlocked(bool);
    bool canJump();
    bool getShouldJump();
    void setShouldJump(bool);
    bool getCanMove();
    void setCanMove(bool);
};
