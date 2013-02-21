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

    void setCoWindow(int, int);
    QDialog *getCoWindow(void);

    void setDataNet(Store*);
    Store *getDataNet(void);

    void setPort(int);
    int getPort(void);

    void setGamesWindow();
    QDialog *getGamesWindow(void);

private:
    QDialog *_coWindow;
    QDialog *_gamesWindow;
    Store   *_dataNet;
    int _port;
};

#endif // MYWINDOW_H
