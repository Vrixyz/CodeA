#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include "MyWindow.h"

class GamesWindow : public QDialog
{
    Q_OBJECT

public:

    GamesWindow(int, int, MyWindow*);
    ~GamesWindow();
    void addToList(int, std::string);

public slots:

    void RecvList();
    void tryToCoGame();

private:

    MyWindow*           _parent;
    QPushButton*        _quit;
    QListWidget*        _list;
    QLabel*             _servLabel;

};

#endif // GAMESWINDOW_H
