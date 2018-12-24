#pragma once

#include <QtWidgets>
#include "checker.h"

class CheckerProto {
public:
    int checker;
    QPoint cell;
    int profit;
    QColor color;
    bool killed;
};

class CheckerProtoMove {
public:
    int checker;
    QPoint from;
    QVector<QPoint> to;
    QColor color;
    bool killed;
    int kills;
};

class ai
{
private:
//    static QVector<CheckerProtoMove *> redMovableCheckers(QVector<CheckerProto *>);
//    static QVector<CheckerProtoMove *> blueMovableCheckers(QVector<CheckerProto *>);
//    static QVector<CheckerProtoMove *> redOneMoreJump(QVector<CheckerProto *>, int);
    static QVector<QPoint> canJump(QVector<CheckerProto *>, QColor, CheckerProto*, CheckerProto*);
    static QVector<QVector<QPoint> > jumpWays(QVector<CheckerProto *>, QColor, CheckerProto*);
    static QVector<CheckerProtoMove *> movableCheckers(QVector<CheckerProto *>, QColor);
public:
    ai();

    static void makeRandomMove();
    static void oneMoreJump(Checker*);
    static void smartMove(int, int, QVector<CheckerProto *>, int, int*, int*, QVector<QPoint> *, QVector<QPoint> *, QVector<QPoint>);
    static void makeSmartMove();
};
