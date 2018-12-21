#pragma once

#include <QtWidgets>
#include "checker.h"

class CheckerProto {
public:
    int checker;
    int i;
    int j;
    int profit;
    QColor color;
    bool killed;
//    CheckerProto(int checker, int i, int j, int profit, QColor color, bool killed) {
//        this->checker = checker;
//        this->i = i;
//        this->j = j;
//        this->profit = profit;
//        this->color = color;
//        this->killed = killed;
//    }
};

class CheckerProtoMove {
public:
    CheckerProtoMove() {

    }
    int checker;
    int i;
    int j;
    int toI;
    int toJ;
    QColor color;
    bool killed;
};

class ai
{
private:
    static QVector<CheckerProtoMove *> redMovableCheckers(QVector<CheckerProto *>);
    static QVector<CheckerProtoMove *> blueMovableCheckers(QVector<CheckerProto *>);
    static QVector<CheckerProtoMove *> redOneMoreJump(QVector<CheckerProto *>, int);
public:
    ai();

    static void makeRandomMove();
    static void oneMoreJump(Checker*);
    static void smartMove(int, QVector<CheckerProto *>, int);
    static void makeSmartMove();
};
