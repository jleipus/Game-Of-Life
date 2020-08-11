#include "game.h"
#include "ui.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game game;
    UI ui(NULL, &game);

    return a.exec();
}
