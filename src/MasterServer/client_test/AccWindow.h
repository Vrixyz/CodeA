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

#include <QListWidgetItem>
#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QList>
#include <QFont>

class Network;

class AccWindow : public QDialog
{
    Q_OBJECT

public:
    AccWindow(int, int, MyWindow *);
    ~AccWindow();

    void creatFields(void);
    void showGames(void);
    void initGames(void);

public slots:
    void checkCo();
    void RecvInfosClient();

private:
    Network             *_soc;

    MyWindow            *_parent;

    QPushButton         *co;
    QPushButton         *quit;
    QLineEdit*          loginEdit;
    QLineEdit*          passwEdit;
    QLabel*             loginLabel;
    QLabel*             passwLabel;
};

#endif // ACCWINDOW_H
