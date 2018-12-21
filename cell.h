#pragma once

#include <QtWidgets>
#include "checker.h"

class Cell: public QWidget
{
    Q_OBJECT
private:
    QColor color;
    int iGrid, jGrid;

    void aiMove();
public:
    Cell(QColor, int, int, QWidget *pwgt = 0);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

    QColor getColor();
    bool hasChecker();
    bool mayMove(QVector<Checker*>, int, int);
    bool mayJump(QVector<Checker*>, int, int, QColor);
signals:
    void moveThisChecker(Checker*, int, int);
};
