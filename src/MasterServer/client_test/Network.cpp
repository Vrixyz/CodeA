#include "MyWindow.h"

Network::Network(QString h, int p)
{
    host = h;
    port = p;
//    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(ReceiveFromServer()));
}

Network::~Network()
{
    soc.close();
}

void    Network::sendToServer(const msgpack::sbuffer& packedInformation)
{
  soc.write(packedInformation.data(), packedInformation.size());
  std::cout << "send " << packedInformation.size()  << std::endl;
}

void    Network::connectToServer()
{
  soc.connectToHost(host, port);
  //    std::cout << "CONNECT " << soc.connectToHost(host, port)  << std::endl;
}

QByteArray    Network::ReceiveFromServer()
{
    QByteArray ligne;
    ligne = soc.readAll();


    std::cout << "RECV " << ligne.length() << std::endl;
    return ligne;
}
