#include "game.h"

Game::Game(const std::string &ip, unsigned int port, MyWindow *w)
{
    angle = 0;
    win = w;
    playerDefinition = NULL;
    selectedUnit = -1;
    scene = new QGraphicsScene(0, 0, 800, 600);
    view = new GameView();
    std::cout << "You just started a new game" << std::endl;
    n = new Nm(QString(ip.c_str()), port, this);
    view->bindNet(n);
    n->connectToServer();
    // Sending information "I want to be a player"
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    packet.pack((int)GameData::Command::BePlayer);
    n->sendToServer(sbuf);
}

Game::~Game()
{
    delete this->n;
    delete this->view;
    delete this->scene;
    this->win->endGame();
}

void Game::setWorld(GameData::World w) {
    world = w;
}

GameData::World Game::getWorld() {
    return (world);
}

void Game::drawWorld() {
    scene->clear();
    //    De quoi vous faire un petit repaire
    QLine ly(0, -300, 0, 300);
    QLine lx(-400, 0, 400, 0);
    scene->addLine(lx);
    scene->addLine(ly);
    for (std::list<Element *>::iterator it = e.begin(); it != e.end(); it++) { // elems physics loop
        (*it)->Draw();
    }
    for (std::list<Unit *>::iterator it = u.begin(); it != u.end(); it++) { // units physics loop
        if ((*it)->unit.id == selectedUnit)
        {
            view->angle = (*it)->physics.angle;
            view->rotationUpdate();
            view->setSceneRect((*it)->physics.x - 400., -300. - (*it)->physics.y, 800, 600);
        }
        (*it)->Draw();
    }
    for (std::list<Bullet *>::iterator it = b.begin(); it != b.end(); it++) { // bullets physics loop
        (*it)->Draw();
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
