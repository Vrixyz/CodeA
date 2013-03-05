#ifndef NM_H
#define NM_H

#include <msgpack.hpp>
#include <QObject>
#include <QTcpSocket>
#include "../../GameData/World.hpp"

class Game;

class Nm : public QObject
{
    Q_OBJECT
public:
    Nm(QString, unsigned int, Game *);
    ~Nm();
    void connectToServer();
    void sendToServer(const msgpack::sbuffer&);
    void updateWorld(QByteArray);
    void updatePlayerDefinition(QByteArray line);
    Game *game;
public slots:
    void ReceiveFromServer();
    void SocError();
private:
    int port;
    QString host;
    QTcpSocket soc;
};

#endif // NM_H
