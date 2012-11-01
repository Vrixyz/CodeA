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
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 400, 400, ui);
    //    QPolygon poly;
    GameData::Physics p;
    for (std::list<GameData::Physics>::iterator it = pelem.begin(); it != pelem.end(); it++) {
        QPolygon *poly = new QPolygon();
        p = *it;
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y);
//            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
//        std::cout << "Elem : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x, p.y);
    }
    for (std::list<GameData::Physics>::iterator it = punit.begin(); it != punit.end(); it++) {
        p = *it;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y);
//            std::cout << c.x << " " << c.y << std::endl;
        }
        if (!(xref || yref)) {
            xref = p.x;
            yref = p.y;
            std::cout << "set default " << xref << " " << yref << std::endl;
        }
        item = scene->addPolygon(*poly);
//        std::cout << "Unit : " << p.x << " " << p.y << " " << punit.size() << std::endl;
        item->setPos(p.x, p.y);
    }
    for (std::list<GameData::Physics>::iterator it = pbullet.begin(); it != pbullet.end(); it++) {
        p = *it;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
//        std::cout << "Bullet : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x, p.y);
    }
    ui->ui->Gameview->setScene(scene);
    //    ui->ui->Gameview->setFixedSize(200, 200);
    ui->ui->Gameview->show();
}
