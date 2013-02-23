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
    void setTabAndAll();
    void createTabNews();
    void createTabServers();
    void createTabSucces();

public slots:

    void RecvList();
    void tryToCoGame();

private:

    MyWindow*           _parent;
    QPushButton*        _quit;
    QListWidget*        _list;

    QTabWidget*         _tab;

    QWidget*            _newsPage;
    QWidget*            _serversPage;
    QWidget*            _succesPage;

};

#endif // GAMESWINDOW_H
