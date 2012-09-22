#ifndef NM_H
#define NM_H

#include "mainwindow.h"
#include <msgpack.hpp>


class Nm : public QObject
{
    Q_OBJECT
public:
    Nm(QString, int);
    ~Nm();
    void connectToServer();
    //    void sendToServer(void *serializedInformation, int length);
public slots:
    void tryReceiveFromServer();
private:
    int port;
    QString host;
    QTcpSocket soc;
};

#endif // NM_H
