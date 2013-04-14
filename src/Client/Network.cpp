#include "MyWindow.h"

Network::Network(QString h, int p)
{
    host = h;
    port = p;
    QObject::connect(&soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocError()));
}


void    Network::SocError()
{
    std::cout << "Cannot connect on ip : " << this->host.toStdString() << " Port : " << this->port << " !" << std::endl;
    exit (0);
}


Network::~Network()
{
    soc.close();
}

void    Network::sendToServer(const msgpack::sbuffer& packedInformation)
{
  std::cout << "SEND:" << packedInformation.size() << std::endl;
  soc.write(packedInformation.data(), packedInformation.size());
}

void    Network::connectToServer()
{
  soc.connectToHost(host, port);
}

QByteArray    Network::ReceiveFromServer()
{
    QByteArray ligne;
    ligne = soc.readAll();

    return ligne;
}
