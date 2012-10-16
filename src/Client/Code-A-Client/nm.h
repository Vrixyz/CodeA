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
    void sendToServer();
    void updateWorld(QByteArray);
public slots:
    void ReceiveFromServer();
private:
    int port;
    QString host;
    QTcpSocket soc;
    Game *game;
};

#endif // NM_H
