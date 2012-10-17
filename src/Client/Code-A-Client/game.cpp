#include "mainwindow.h"
#include "ui_mainwindow.h"

Game::Game(MainWindow *u)
{
    ui = u;
}

void Game::setWorld(GameData::World w) {
    world = w;
}

GameData::World Game::getWorld() {
    return (world);
}

void Game::drawWorld() {
    QGraphicsItem *item;
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 800, 600, ui);
    QPixmap grass("./grass.png");
    GameData::Physics p;
    for (std::list<GameData::Physics>::iterator it = pelem.begin(); it != pelem.end(); ++it) {
        p = *it;
        item = scene->addPixmap(grass);
        item->setPos(p.x, p.y);
        std::cout << "draw elem x : " << p.x << " draw elem y : " << p.y << std::endl;
    }
    for (std::list<GameData::Physics>::iterator it = punit.begin(); it != punit.end(); ++it) {
        p = *it;
        item = scene->addPixmap(grass);
        item->setPos(p.x, p.y);
        std::cout << "draw unit x : " << p.x << " draw unit y : " << p.y << std::endl;
    }
    for (std::list<GameData::Physics>::iterator it = pbullet.begin(); it != pbullet.end(); ++it) {
        p = *it;
        item = scene->addPixmap(grass);
        item->setPos(p.x, p.y);
        std::cout << "draw bullet x : " << p.x << " draw bullet y : " << p.y << std::endl;
    }
    ui->ui->Gameview->setScene(scene);
    ui->ui->Gameview->show();
}
