#include "checker.h"
#include "gameboard.h"
#include "game.h"

void Checker::drawChecker()
{
    QPainter painter(this);
    painter.setBrush(QBrush(color));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(5, 5, width() - 10, height() - 10);
    painter.end();
}

void Checker::drawActiveChecker()
{
    QRadialGradient gradient(width() / 2, height() / 2, width());
    gradient.setColorAt(0, color);
    gradient.setColorAt(1, Qt::white);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawEllipse(0, 0, width(), height());
    painter.setBrush(QBrush(color));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(5, 5, width() - 10, height() - 10);
    painter.end();
}

void Checker::drawQueen()
{
    if (color == Qt::red) {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::darkRed));
        painter.drawEllipse(5, 5, width() - 10, height() - 10);
        painter.end();
    }
    if (color == Qt::blue) {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::darkBlue));
        painter.drawEllipse(5, 5, width() - 10, height() - 10);
        painter.end();
    }
}

void Checker::drawActiveQueen()
{
    if (color == Qt::red) {
        QRadialGradient gradient(width() / 2, height() / 2, width());
        gradient.setColorAt(0, Qt::darkRed);
        gradient.setColorAt(1, Qt::white);
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(gradient);
        painter.drawEllipse(0, 0, width(), height());
        painter.setBrush(QBrush(Qt::darkRed));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(5, 5, width() - 10, height() - 10);
        painter.end();
    }
    if (color == Qt::blue) {
        QRadialGradient gradient(width() / 2, height() / 2, width());
        gradient.setColorAt(0, Qt::darkBlue);
        gradient.setColorAt(1, Qt::white);
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(gradient);
        painter.drawEllipse(0, 0, width(), height());
        painter.setBrush(QBrush(Qt::darkBlue));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(5, 5, width() - 10, height() - 10);
        painter.end();
    }
}

Checker::Checker(int iGrid, int jGrid, QColor color, QWidget *)
{
    setFixedSize(44, 44);
    this->iGrid = iGrid;
    this->jGrid = jGrid;
    this->color = color;
    isClicked = false;
    blocked = false;
    isQueen = false;
    shouldJump = false;
    canMove = true;
}

void Checker::paintEvent(QPaintEvent *)
{
//    int w, h;
//    if (window()->width() > 700)
//        w =
    if (isClicked) {
        if (isQueen)
            drawActiveQueen();
        else
            drawActiveChecker();
    }
    else {
        if (isQueen)
            drawQueen();
        else
            drawChecker();
    }
}

void Checker::mousePressEvent(QMouseEvent *)
{
    GameBoard *gm = qobject_cast<GameBoard*>(this->parent());
    if (isClicked && !shouldJump) {
        isClicked = false;
        gm->setHasActiveChecker(false);
    }
    else if (!gm->getHasActiveChecker() && color == Qt::blue && !blocked) {
        isClicked = true;
        gm->setHasActiveChecker(true);
    }
    else if (gm->getHasActiveChecker() && color == Qt::blue && !blocked) {
        gm->getActiveChecker()->deactivate();
        isClicked = true;
        gm->setHasActiveChecker(true);
    }
    update();
}

bool Checker::getIsClicked()
{
    return isClicked;
}

int Checker::getI()
{
    return iGrid;
}

int Checker::getJ()
{
    return jGrid;
}

void Checker::setI(int i)
{
    iGrid = i;
    if (color == Qt::red && iGrid == 7) {
        isQueen = true;
    }
    if (color == Qt::blue && iGrid == 0) {
        isQueen = true;
    }
}

void Checker::setJ(int j)
{
    jGrid = j;
}

QColor Checker::getColor()
{
    return color;
}

void Checker::activate()
{
    GameBoard *gm = game->getGB();
    //GameBoard *gm = qobject_cast<GameBoard*>(this->parent());
    gm->setHasActiveChecker(false);
    isClicked = true;
    update();
}

void Checker::deactivate()
{
    GameBoard *gm = game->getGB();
    //GameBoard *gm = qobject_cast<GameBoard*>(this->parent());
    gm->setHasActiveChecker(false);
    isClicked = false;
    update();
}

bool Checker::getBlocked()
{
    return blocked;
}

void Checker::setBlocked(bool blocked)
{
    this->blocked = blocked;
}

bool Checker::canJump()
{
    GameBoard *gb = game->getGB();
    QVector<QVector<Cell *> > cells = gb->getCells();
    QVector<Checker *> checkers = gb->getCheckers();
    for (int j = 0; j < 4; ++j) {
        int signX = qCos((j / 2) * M_PI);
        int signY = qCos(((j + 1) / 2) * M_PI);
        int cellX = (iGrid + 2 * signX);
        int cellY = (jGrid + 2 * signY);
        if (cellX >= 0 && cellX <= 7 && cellY >= 0 && cellY <= 7) {
            if (cells[cellX][cellY]->mayJump(checkers, iGrid, jGrid, color)) {
                return true;
            }
        }
    }
    return false;
}

bool Checker::getShouldJump()
{
    return shouldJump;
}

void Checker::setShouldJump(bool f)
{
    shouldJump = f;
}

bool Checker::getCanMove()
{
    return canMove;
}

void Checker::setCanMove(bool f)
{
    canMove = f;
}

