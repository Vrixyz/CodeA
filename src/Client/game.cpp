#include "game.h"

Game::Game(const std::string &ip, unsigned int port, const std::string &type, MyWindow *w)
{
    isRTS = type == "class1" ? true : false;
    w->setFixedSize(800, 600);
    angle = 0;
    win = w;
    playerDefinition = NULL;
    selectedUnit = -1;
    scene = new QGraphicsScene(0, 0, 800, 600);
    view = new GameView(w);
    std::cout << "You just started a new game" << std::endl;
    n = new Nm(QString(ip.c_str()), port, this);
    view->bindNet(n);
    n->connectToServer();
    // Sending information "I want to be a player"
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    packet.pack((int)GameData::Command::BePlayer);
    GameData::CommandStruct::BePlayer player;
    if (isRTS)
        player.type = GameData::CommandStruct::BePlayer::INVOKER;
    else
        player.type = GameData::CommandStruct::BePlayer::MAGE;
    player.login = "osella";
    packet.pack(player);
    n->sendToServer(sbuf);
    view->setScene(scene);
    view->show();
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
    //    De quoi vous faire un petit repaire
     QLine ly(0, -300, 0, 300);
     QLine lx(-400, 0, 400, 0);
     scene->addLine(lx);
     scene->addLine(ly);
    view->viewMove();
    for (std::list<Unit *>::iterator it = u.begin(); it != u.end(); it++) // units physics loop
        if ((*it)->unit.id == selectedUnit && isRTS == false)
        {
            view->angle = (*it)->physics.angle;
            view->rotationUpdate();
            view->setSceneRect((*it)->physics.x - 400., -300. - (*it)->physics.y, 800, 600);
        }
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
