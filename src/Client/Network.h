#ifndef NETWORK_H
#define NETWORK_H

#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

#include <iostream>
#include <list>

#include <QTcpSocket>
#include <QtGui>

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
    QTcpSocket *getSock() {return &soc;}

public slots:

   QByteArray    ReceiveFromServer();

private:

    int port;
    QString host;
    QTcpSocket soc;

};

#endif // NETWORK_H

