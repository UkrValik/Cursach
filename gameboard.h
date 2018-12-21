#pragma once

#include <QtWidgets>
#include "cell.h"
#include "checker.h"

class GameBoard: public QWidget
{
    Q_OBJECT
private:
    QVector<QVector<Cell*> > cells;
    QVector<Checker*> redCheckers;
    QVector<Checker*> blueCheckers;
    QGridLayout *myLayout;
    bool hasActiveChecker;
public:
    GameBoard(QWidget *pwgt = Q_NULLPTR);

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);

    bool getHasActiveChecker();
    void setHasActiveChecker(bool);
    Checker *getActiveChecker();
    QVector<Checker *> getCheckers();
    QVector<QVector<Cell *> > getCells();
    QGridLayout *getLayout();
    void removeChecker(int, int);

public slots:
    void moveChecker(Checker*, int, int);
};
