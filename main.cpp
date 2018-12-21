#include <QtWidgets>
#include "game.h"

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);

    game = new Game();

    return app->exec();
}
