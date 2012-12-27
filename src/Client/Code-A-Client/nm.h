#ifndef NM_H
#define NM_H

#include "mainwindow.h"
#include <msgpack.hpp>
#include "../../GameData/World.hpp"

class Game;

class Nm : public QObject
{
    Q_OBJECT
public:
    Nm(QString, int, Game *);
    ~Nm();
    void connectToServer();
    void sendToServer(const msgpack::sbuffer&);
    void updateWorld(QByteArray);
    void updatePlayerDefinition(QByteArray line);
    Game *game;
public slots:
    void ReceiveFromServer();
private:
    int port;
    QString host;
    QTcpSocket soc;
};

#endif // NM_H
