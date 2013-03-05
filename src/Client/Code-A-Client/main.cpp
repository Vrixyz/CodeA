#include <QtGui/QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Client");
    Game *game = new Game("127.0.0.1", 4123);
    return a.exec();
}
