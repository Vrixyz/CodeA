#include "MyWindow.h"

Network::Network(QString h, int p)
{
    host = h;
    port = p;
    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(ReceiveFromServer()));
}

Network::~Network()
{
    soc.close();
}

void    Network::sendToServer(const msgpack::sbuffer& packedInformation)
{
    int i;

    i = soc.write(packedInformation.data(), packedInformation.size());
    std::cout << "send " << packedInformation.size()  << std::endl;
}

void    Network::connectToServer()
{
  soc.connectToHost(host, port);
  //    std::cout << "CONNECT " << soc.connectToHost(host, port)  << std::endl;
}

void    Network::ReceiveFromServer()
{
    std::cout << "received" << std::endl;
    QByteArray ligne;
    ligne = soc.readAll();
    try
    {
        msgpack::unpacker pac;
        pac.reserve_buffer(ligne.length());
        memcpy(pac.buffer(), ligne.data(), ligne.length());
        pac.buffer_consumed(ligne.length());
        msgpack::unpacked result;
        if (pac.next(&result)) {
            int idData;
            result.get().convert(&idData);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << e.what() << std::endl;
    }
}
