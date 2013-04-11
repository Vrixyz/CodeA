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
    void createTabSucces1();
    void createTabSucces2();
    void RecvList(QByteArray res);
    void RecvChat(QByteArray res);
    void RecvError(QByteArray res);
    void RecvServer(QByteArray res);

public slots:

    void sendMsg();
    void RecvData();
    void tryToCoGame();
    void refreshServ();
    void tryToMatchmaking();

private:

    MyWindow*           _parent;

    QPushButton*        _quit;
    QPushButton*        _join;
    QPushButton*        _match;
    QPushButton*        _refresh;

    QListWidget*        _list;

    QTabWidget*         _tab;

    QLabel*             _imgSucc1[20];
    QLabel*             _imgSucc2[25];
    QLabel*             _imgLock1[20];
    QLabel*             _imgLock2[25];

    QLabel*             _iServ;
    QLabel*             _iIp;
    QLabel*             _iPort;

    QWidget*            _newsPage;
    QWidget*            _serversPage;
    QWidget*            _succesPage;

    QTextEdit*          _readChat;

    QLineEdit*          _writeChat;

};

#endif // GAMESWINDOW_H
