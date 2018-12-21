#pragma once

#include <QtWidgets>
#include "buttons.h"

class Interface : public QWidget
{
    Q_OBJECT
private:
    NewGameButton *newGame;
    LoadSavedGameButton *loadSavedGame;
    AboutButton *about;
    ExitButton *exit;
public:
    Interface(QWidget *pwgt = Q_NULLPTR);


};
