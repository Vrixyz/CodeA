#include "GamesWindow.h"

GamesWindow::GamesWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    quit = new QPushButton("Quitter", this);
    quit->setFont(QFont("", 12, 0));
    quit->setGeometry(100, 340, 200, 40);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

GamesWindow::~GamesWindow()
{
}
