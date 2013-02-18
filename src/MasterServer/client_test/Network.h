#ifndef NETWORK_H
#define NETWORK_H

#include "MyWindow.h"
#include <msgpack.hpp>

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

