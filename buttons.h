#pragma once

#include <QtWidgets>

class NewGameButton : public QPushButton
{
private:
    QString text;
public:
    NewGameButton(QString, QWidget *pwgt = Q_NULLPTR);

    void mousePressEvent(QMouseEvent *);
};

class LoadSavedGameButton : public QPushButton
{
private:
    QString text;
public:
    LoadSavedGameButton(QString, QWidget *pwgt = Q_NULLPTR);
};

class AboutButton : public QPushButton
{
private:
    QString text;
public:
    AboutButton(QString, QWidget *pwgt = Q_NULLPTR);
};

class ExitButton : public QPushButton
{
private:
    QString text;
public:
    ExitButton(QString, QWidget *pwgt = Q_NULLPTR);

    void mousePressEvent(QMouseEvent *);
};
