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
    void creatFields4SuPage(void);
    void showGames(void);
    void initGames(void);

    void setTab();
    void setCoPage();
    void setSuPage();

public slots:
    void checkCo();
    void checkSu();
    void RecvInfosClient();

private:

    /* Classe des sockets, etc. */

    Network*            _soc;

    /* Fenetre principale */

    MyWindow*           _parent;

    /* Tableau d'onglets */

    QTabWidget*         _tabConnexion;
    QWidget*            _page1;
    QWidget*            _page2;

    /* Boutons + Fields + Labels pour la connexion */

    QPushButton*        _co;
    QPushButton*        _CoQuit;

    QLineEdit*          _loginEdit;
    QLineEdit*          _passwEdit;

    QLabel*             _loginLabel;
    QLabel*             _passwLabel;

    /* Boutons + Fields + Labels pour l'inscription */

    QPushButton*        _su;
    QPushButton*        _SuQuit;

    QLineEdit*          _loginSuEdit;
    QLineEdit*          _passw1SuEdit;
    QLineEdit*          _passw2SuEdit;
    QLineEdit*          _mailEdit;

    QLabel*             _loginSuLabel;
    QLabel*             _passw1SuLabel;
    QLabel*             _passw2SuLabel;
    QLabel*             _mailLabel;
};

#endif // ACCWINDOW_H
