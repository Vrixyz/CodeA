#ifndef NETWORK_H
#define NETWORK_H

#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

#include <iostream>
#include <list>

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

#include <msgpack.hpp>

struct s_game
{
    int id;
    int size;
    std::string name;
} typedef t_game;

class Network : public QObject
{
    Q_OBJECT

public:
    Network(QString, int);
    ~Network();
    void connectToServer();
    void sendToServer(const msgpack::sbuffer&);

public slots:
    void ReceiveFromServer();
private:
    int port;
    QString host;
    QTcpSocket soc;
};

#endif // NETWORK_H

