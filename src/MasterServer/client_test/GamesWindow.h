#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include "MyWindow.h"

class GamesWindow : public QDialog
{
    Q_OBJECT

public:
    GamesWindow(int, int, MyWindow*);
    ~GamesWindow();
public slots:
    void RecvList();
private:
    MyWindow*           _parent;
    QPushButton*        quit;
    std::list<t_game>   _allGames;
    QListWidget         *list;
};

#endif // GAMESWINDOW_H
