#include "interface.h"

Interface::Interface(QWidget *)
{
    setMinimumSize(400, 300);
    newGame = new NewGameButton("Нова гра");
    loadSavedGame = new LoadSavedGameButton("Завантажити збережену гру");
    about = new AboutButton("Деталі");
    exit = new ExitButton("Вихід");
    newGame->setFixedSize(200, 70);
    loadSavedGame->setFixedSize(200, 70);
    about->setFixedSize(200, 70);
    exit->setFixedSize(200, 70);
    QGridLayout *inLayout = new QGridLayout();
    inLayout->setContentsMargins(100, 50, 100, 50);
    inLayout->setSpacing(50);
    inLayout->addWidget(newGame, 0, 0);
    inLayout->addWidget(loadSavedGame, 1, 0);
    inLayout->addWidget(about, 2, 0);
    inLayout->addWidget(exit, 3, 0);
    setLayout(inLayout);
}
