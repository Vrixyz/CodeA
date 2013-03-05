#include "game.h"

Nm::Nm(QString h, unsigned int p, Game *g)
{
    game = g;
    host = h;
    port = p;
    QObject::connect(&soc, SIGNAL(readyRead()), this, SLOT(ReceiveFromServer()));
    QObject::connect(&soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocError()));
}

Nm::~Nm()
{
    soc.disconnectFromHost();
    soc.close();
}

void    Nm::sendToServer(const msgpack::sbuffer& packedInformation)
{
    int i;
    i = soc.write(packedInformation.data(), packedInformation.size());
    std::cout << "send " << i << " " << packedInformation.size() << std::endl;
}

void    Nm::connectToServer()
{
    try
    {
        soc.connectToHost(host, port);
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << e.what() << std::endl;
    }
}

void    Nm::ReceiveFromServer()
{
//    std::cout << "received" << std::endl;
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

            if (idData == GameData::InformationId::PlayerDefinition)
            {
                this->updatePlayerDefinition(ligne);
            }
            else if (idData == GameData::InformationId::EntireWorld)
            {
                this->updateWorld(ligne);
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << e.what() << std::endl;
    }
}

void    Nm::SocError()
{
    std::cout << "Cannot connect !" << std::endl;
    exit (0);
}

void    Nm::updatePlayerDefinition(QByteArray line)
{
    msgpack::unpacker pac;
    pac.reserve_buffer(line.length());
    memcpy(pac.buffer(), line.data(), line.length());
    pac.buffer_consumed(line.length());
    msgpack::unpacked result;
    pac.next(&result); // remove unused id
    GameData::Information::PlayerDefinition playerDefinition;
    pac.next(&result); // get the playerDefinition
    result.get().convert(&playerDefinition);
    game->setPlayerDefinition(playerDefinition);
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
    pac.next(&result); // remove unused id
    if (pac.next(&result)) {
        result.get().convert(&woo);
        game->e.clear();
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
            GameData::Element e(0,false);
            result.get().convert(&e);
            pac.next(&result);
            result.get().convert(&p);
            Element *el = new Element(e, p, game->scene);
            game->e.push_back(el);
            game->elem.push_back(e);
            game->pelem.push_back(p);
	    //            std::cout << "angle: " << p.angle << std::endl;
            //std::cout << "1 elem" << std::endl;
        }
        //std::cout << "over" << std::endl;
        for (i = 0; i < woo.nbUnit; i++)
        {
            pac.next(&result);
            GameData::Unit u(0,0);
            result.get().convert(&u);


            if (game->playerDefinition && game->playerDefinition->idPlayer == (int)u.playersId.front())
                // we make the client select the first unit sent by server owned by the player associated.
                game->setSelection(u.id);

            pac.next(&result);
            result.get().convert(&p);
            game->unit.push_back(u);
            game->punit.push_back(p);
        }
        for (i = 0; i < woo.nbBullet; i++)
        {
            pac.next(&result);
            GameData::Bullet b(1, 0);
            result.get().convert(&b);
            pac.next(&result);
            result.get().convert(&p);
            game->bullet.push_back(b);
            game->pbullet.push_back(p);
        }
        game->drawWorld();
    }
}
