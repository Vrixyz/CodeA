#ifndef GAMESWINDOW_H
#define GAMESWINDOW_H

#include "MyWindow.h"

class GamesWindow : public QDialog
{
    Q_OBJECT

public:

    GamesWindow(int, int, MyWindow*);
    ~GamesWindow();
    void SendCMD(int cmd);
    void addToList(int, std::string);
    void setTabAndAll();
    void createTabNews();
    void createTabServers();
    void createTabSucces();
    void createTabSucces1(std::string);
    void createTabSucces2(std::string);
    void RecvList(QByteArray res);
    void RecvChat(QByteArray res);
    void RecvError(QByteArray res);
    void RecvServer(QByteArray res);
    void RecvSucces(QByteArray res);
    void UpdateAllSucces();

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
    QWidget*            _succesPage1;
    QWidget*            _succesPage2;

    QTextEdit*          _readChat;

    QLineEdit*          _writeChat;

    std::string         _succ1;
    std::string         _succ2;

};

#endif // GAMESWINDOW_H
