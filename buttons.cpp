#include "buttons.h"
#include "game.h"

NewGameButton::NewGameButton(QString text, QWidget *)
{
    this->text = text;
    setText(text);
}

void NewGameButton::mousePressEvent(QMouseEvent *)
{
    game->getGB()->show();
    window()->close();
}

LoadSavedGameButton::LoadSavedGameButton(QString text, QWidget *)
{
    this->text = text;
    setText(text);
}

AboutButton::AboutButton(QString text, QWidget *)
{
    this->text = text;
    setText(text);
}

ExitButton::ExitButton(QString text, QWidget *)
{
    this->text = text;
    setText(text);
}

void ExitButton::mousePressEvent(QMouseEvent *)
{
    window()->close();
}
