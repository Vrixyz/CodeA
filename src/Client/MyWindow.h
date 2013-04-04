#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "../MasterData/MasterData.hpp"
#include "../MasterData/ServList.hpp"
#include "../MasterData/Command.hpp"
#include "../MasterData/Co.hpp"

#include <iostream>
#include <list>

#include "Network.h"
#include "Store.h"

#include "game.h"

#include <QtGui>

class Network;

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:

    MyWindow(int, int);
    ~MyWindow();

    QDialog *getGamesWindow(void);
    QDialog *getAccWindow(void);
    QDialog *getSuWindow(void);

    void setDataNet(Store*);
    Store *getDataNet(void);

    void setPort(int);
    int getPort(void);

    void	setIP(QString);
    QString	getIP(void);

    void startGame(void);
    void endGame(void);

public slots:

    void setGamesWindow();
    void setClassWindow();
    void setAccWindow();
    void setSuWindow();

private:
    QString	_ip;
    int		_port;

    QDialog *	_accWindow;
    QDialog *	_suWindow;
    QDialog *	_gamesWindow;
    QDialog *	_classWindow;

    Store   *	_dataNet;

    Game    *	_game;
};

#endif // MYWINDOW_H
