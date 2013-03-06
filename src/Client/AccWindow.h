#ifndef ACCWINDOW_H
#define ACCWINDOW_H

#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

#include <iostream>
#include <list>

#include "MyWindow.h"
#include "Network.h"
#include "Define.h"
#include "Store.h"

#include <QtGui>

class Network;

class AccWindow : public QDialog
{
    Q_OBJECT

public:

    AccWindow(int, int, MyWindow *);
    ~AccWindow();

    void creatFields4CoPage(void);
    void showGames(void);
    void initGames(void);
    void setCoPage();

public slots:

    void checkCo();
    void RecvInfosClient();

private:

    Network*            _soc;

    MyWindow*           _parent;

    QPushButton*        _co;
    QPushButton*        _su;
    QPushButton*        _CoQuit;

    QLineEdit*          _loginEdit;
    QLineEdit*          _passwEdit;

    QLabel*             _loginLabel;
    QLabel*             _passwLabel;

};

#endif // ACCWINDOW_H
