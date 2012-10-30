#include "mainwindow.h"
#include "ui_mainwindow.h"

Game::Game(MainWindow *u)
{
    xref = 0;
    yref = 0;
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
    GameData::Physics::Coord c;
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 800, 600, ui);
    // FIXME: use ressource loading
    QPolygon poly;
//    QPixmap grass("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/grass.png");
    GameData::Physics p;
    for (std::list<GameData::Physics>::iterator it = pelem.begin(); it != pelem.end(); ++it) {
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ++ite) {
            c = *ite;
            poly << QPoint(c.x, c.y);
//            std::cout << c.x << " " << c.y << std::endl;
        }
        p = *it;
        item = scene->addPolygon(poly);
        item->setPos(p.x, p.y);
        poly.empty();
    }
    for (std::list<GameData::Physics>::iterator it = punit.begin(); it != punit.end(); ++it) {
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ++ite) {
            c = *ite;
            poly << QPoint(c.x, c.y);
//            std::cout << c.x << " " << c.y << std::endl;
        }
        p = *it;
        if (!(xref || yref)) {
            xref = p.x;
            yref = p.y;
            std::cout << "set default " << xref << " " << yref << std::endl;
        }
        item = scene->addPolygon(poly);
        item->setPos(p.x, p.y);
        poly.empty();
    }
    for (std::list<GameData::Physics>::iterator it = pbullet.begin(); it != pbullet.end(); ++it) {
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ++ite) {
            c = *ite;
            poly << QPoint(c.x, c.y);
//            std::cout << c.x << " " << c.y << std::endl;
        }
        p = *it;
        item = scene->addPolygon(poly);
        item->setPos(p.x, p.y);
        poly.empty();
    }
    ui->ui->Gameview->setScene(scene);
    ui->ui->Gameview->show();
}
