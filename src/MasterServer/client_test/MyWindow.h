#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/ServList.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

#include <iostream>
#include <list>

#include "Network.h"
#include "Store.h"

#include <QtGui>

class Network;

class MyWindow : public QWidget
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

    void startGame(int, std::string);
    void endGame(void);

public slots:

    void setGamesWindow();
    void setClassWindow();
    void setAccWindow();
    void setSuWindow();

private:

    int _port;

    QDialog *_accWindow;
    QDialog *_suWindow;
    QDialog *_gamesWindow;
    QDialog *_classWindow;

    Store   *_dataNet;

};

#endif // MYWINDOW_H
