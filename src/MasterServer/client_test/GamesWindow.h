#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include "MyWindow.h"

class GamesWindow : public QDialog
{
public:
    GamesWindow(int, int, MyWindow*);
    ~GamesWindow();
private:
    QWidget*            _parent;
    QPushButton*        quit;
    std::list<t_game>   _allGames;
    QListWidget         *list;
};

#endif // GAMESWINDOW_H
