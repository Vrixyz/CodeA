#include "mainwindow.h"

Nm::Nm(QString h, int p, Game *g)
{
    game = g;
    host = h;
    port = p;
    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(ReceiveFromServer()));
}

Nm::~Nm()
{

}

void    Nm::sendToServer(const msgpack::sbuffer& packedInformation)
{
    soc.write(packedInformation.data());
    std::cout << "send" << std::endl;
}

void    Nm::connectToServer()
{
    soc.connectToHost(host, port);
    std::cout << "connected" << std::endl;
}

void    Nm::ReceiveFromServer()
{
    QByteArray ligne;
    ligne = soc.readAll();
    try
    {
        this->updateWorld(ligne);
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << e.what() << std::endl;
    }
}

void    Nm::updateWorld(QByteArray ligne) {
    msgpack::unpacker pac;
    pac.reserve_buffer(ligne.length());
    memcpy(pac.buffer(), ligne.data(), ligne.length());
    pac.buffer_consumed(ligne.length());
    u_int32_t i;
    GameData::World woo;
    msgpack::unpacked result;
    GameData::Physics p;
    GameData::Bullet b(0, 0);
    GameData::Unit u(0, 0);
    GameData::Element e(0, false);
    if (pac.next(&result)) {
        result.get().convert(&woo);
        game->setWorld(woo);
        game->unit.clear();
        game->punit.clear();
        game->elem.clear();
        game->pelem.clear();
        game->bullet.clear();
        game->pbullet.clear();
        for (i = 0; i < woo.nbElement; i++)
        {
            pac.next(&result);
            result.get().convert(&e);
            pac.next(&result);
            result.get().convert(&p);
            game->elem.push_back(e);
            game->pelem.push_back(p);
        }
        for (i = 0; i < woo.nbUnit; i++)
        {
            pac.next(&result);
            result.get().convert(&u);
            pac.next(&result);
            result.get().convert(&p);
            game->unit.push_back(u);
            game->punit.push_back(p);
        }
        for (i = 0; i < woo.nbBullet; i++)
        {
            pac.next(&result);
            result.get().convert(&b);
            pac.next(&result);
            result.get().convert(&p);
            game->bullet.push_back(b);
            game->pbullet.push_back(p);
        }
        game->drawWorld();
    }
}
