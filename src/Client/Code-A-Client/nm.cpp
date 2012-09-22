#include "nm.h"

Nm::Nm(QString h, int p)
{
    host = h;
    port = p;
    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(tryReceiveFromServer()));
}

Nm::~Nm()
{

}

//void    Nm::sendToServer()
//{
//QTextStream texte(&soc);
//texte << t <<endl;
//}

void    Nm::connectToServer()
{
    soc.connectToHost(host, port);
    std::cout << "connected" << std::endl;
}

void    Nm::tryReceiveFromServer()
{
    int i = 0;
    std::cout << "founded" << std::endl;
    QByteArray ligne;
    i = soc.bytesAvailable();
    ligne = soc.readAll();
    std::cout << i << " " << ligne.length() << std::endl;
    write(1, ligne.data(), 127);
    std::cout << std::endl;
    try
    {
        msgpack::unpacker pac;
        pac.reserve_buffer(i);
        memcpy(pac.buffer(), ligne.data(), i);
        pac.buffer_consumed(i);
        msgpack::unpacked result;
        while(pac.next(&result)) {
            std::cout << "unpacked : " << result.get() << std::endl;
        }
        std::cout << "done" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
