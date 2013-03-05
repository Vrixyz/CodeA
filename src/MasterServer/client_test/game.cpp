#include "game.h"

Game::Game(QMainWindow *w)
{
    angle = 0;
    win = w;
    playerDefinition = NULL;
    selectedUnit = -1;
    scene = new QGraphicsScene(0, 0, 800, 600);
    view = new GameView();
    std::cout << "You just started a new game" << std::endl;
    n = new Nm("127.0.0.1", 4242, this);
    view->bindNet(n);
    n->connectToServer();
    // Sending information "I want to be a player"
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    packet.pack((int)GameData::Command::BePlayer);
    n->sendToServer(sbuf);
}

void Game::setWorld(GameData::World w) {
    world = w;
}

GameData::World Game::getWorld() {
    return (world);
}

void Game::drawWorld() {
    QGraphicsItem *item;
    GameData::Physics::Coord c;
    scene->clear();
    GameData::Physics p;
    GameData::Unit u(0, 0);
    //    De quoi vous faire un petit repaire
    QLine ly(0, -300, 0, 300);
    QLine lx(-400, 0, 400, 0);
    scene->addLine(lx);
    scene->addLine(ly);
    std::list<GameData::Unit>::iterator unitit = unit.begin();
    for (std::list<GameData::Physics>::iterator it = pelem.begin(); it != pelem.end(); it++) { // elems physics loop
        QPolygon *poly = new QPolygon();
        p = *it;
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
        item->setRotation(p.angle);
        //        std::cout << "Elem : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
    }
    unitit = unit.begin();
    for (std::list<GameData::Physics>::iterator it = punit.begin(); it != punit.end(); it++, unitit++) { // units physics loop
        p = *it;
        u = *unitit;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
        if (u.id == selectedUnit)
        {
            view->angle = p.angle;
            view->rotationUpdate();
            item->setRotation(view->angle);
            view->setSceneRect(p.x - 400., -300. - p.y, 800, 600);
        }
        //        std::cout << "Unit : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
        item->setRotation(p.angle);
    }
    for (std::list<GameData::Physics>::iterator it = pbullet.begin(); it != pbullet.end(); it++) { // bullets physics loop
        p = *it;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        scene->addEllipse(p.x, p.y * -1, 5, 5);
        item = scene->addPolygon(*poly);
        //        std::cout << "Bullet : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
    }
    view->setScene(scene);
    view->show();
}

void Game::setPlayerDefinition(const GameData::Information::PlayerDefinition& pd)
{
    delete playerDefinition;
    playerDefinition = new GameData::Information::PlayerDefinition(pd);
}

void Game::setSelection(int unitId)
{
    selectedUnit = unitId;
}
