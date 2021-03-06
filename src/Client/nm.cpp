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
    soc.write(packedInformation.data(), packedInformation.size());
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
    std::cout << "Cannot connect on ip : " << this->host.toStdString() << " Port : " << this->port << " !" << std::endl;
    soc.disconnectFromHost();
    soc.close();
    delete game;
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
        resetAll();
        game->setWorld(woo);
        for (i = 0; i < woo.nbElement; i++)
        {
            pac.next(&result);
            GameData::Element e(0,false);
            result.get().convert(&e);
            pac.next(&result);
            result.get().convert(&p);
            Element *el = new Element(e, p, game->scene);
            updateElem(el);
        }
        deleteElem();
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
            Unit *un = new Unit(u, p, game->scene);
            updateUnit(un);
        }
        deleteUnit();
        for (i = 0; i < woo.nbBullet; i++)
        {
            pac.next(&result);
            GameData::Bullet b(1, 0);
            result.get().convert(&b);
            pac.next(&result);
            result.get().convert(&p);
            Bullet *bu = new Bullet(b, p, game->scene);
            updateBullet(bu);
        }
        deleteBullet();
        game->drawWorld();
    }
}

bool Nm::updateElem(Element *e)
{
    for (std::list<Element *>::iterator it = game->e.begin(); it != game->e.end(); it++) {
        if ((*it)->elem.id == e->elem.id)
        {
            (*it)->elem = e->elem;
            (*it)->physics = e->physics;
            delete e;
            (*it)->exist = true;
            return true;
        }
    }
    std::cout << "pushed elem" << game->e.size() << std::endl;
    game->e.push_back(e);
    e->Draw();
    return false;
}

bool Nm::updateUnit(Unit *u)
{
    for (std::list<Unit *>::iterator it = game->u.begin(); it != game->u.end(); it++) {
        if ((*it)->unit.id == u->unit.id)
        {
            (*it)->unit = u->unit;
            (*it)->physics = u->physics;
            delete u;
            (*it)->exist = true;
            return true;
        }
    }
    std::cout << "pushed unit" << game->u.size() << std::endl;
    game->u.push_back(u);
    u->Draw();
    return false;
}

bool Nm::updateBullet(Bullet *b)
{
    for (std::list<Bullet *>::iterator it = game->b.begin(); it != game->b.end(); it++) {
        if ((*it)->bullet.id == b->bullet.id)
        {
            (*it)->bullet = b->bullet;
            (*it)->physics = b->physics;
            delete b;
            (*it)->exist = true;
            return true;
        }
    }
    std::cout << "pushed bullet : " << game->b.size() << std::endl;
    game->b.push_back(b);
    b->Draw();
    return false;
}

void Nm::deleteElem()
{
    for (std::list<Element *>::iterator it = game->e.begin(); it != game->e.end(); it++) {
        if ((*it)->exist == false)
        {
            std::cout << "remove elem" << std::endl;
            game->scene->removeItem(*it);
            it = game->e.erase(it);
        }
    }
}

void Nm::deleteUnit()
{
    for (std::list<Unit *>::iterator it = game->u.begin(); it != game->u.end(); it++) {
        if ((*it)->exist == false)
        {
            std::cout << "remove unit" << std::endl;
            game->scene->removeItem(*it);
            it = game->u.erase(it);
        }
    }
}

void Nm::deleteBullet()
{
    for (std::list<Bullet *>::iterator it = game->b.begin(); it != game->b.end(); it++) {
        if ((*it)->exist == false)
        {
            std::cout << "remove bullet" << std::endl;
            game->scene->removeItem(*it);
            it = game->b.erase(it);
        }
    }
}

void Nm::resetAll()
{
    for (std::list<Element *>::iterator it = game->e.begin(); it != game->e.end(); it++)
        (*it)->exist = false;
    for (std::list<Unit *>::iterator it = game->u.begin(); it != game->u.end(); it++)
        (*it)->exist = false;
    for (std::list<Bullet *>::iterator it = game->b.begin(); it != game->b.end(); it++)
        (*it)->exist = false;
}
