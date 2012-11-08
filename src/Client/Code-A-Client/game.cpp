#include "mainwindow.h"
#include "ui_mainwindow.h"

Game::Game(MainWindow *u, GameView *v)
{
    angle = 0;
    ui = u;
    view = v;
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
    GameData::Physics p;
    //    De quoi vous faire un petit repaire
    QLine ly(0, -300, 0, 300);
    QLine lx(-400, 0, 400, 0);
    scene->addLine(lx);
    scene->addLine(ly);
    for (std::list<GameData::Physics>::iterator it = pelem.begin(); it != pelem.end(); it++) {
        QPolygon *poly = new QPolygon();
        p = *it;
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
//        std::cout << "Elem : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
    }
    for (std::list<GameData::Physics>::iterator it = punit.begin(); it != punit.end(); it++) {
        p = *it;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
        view->setSceneRect(p.x - 400., -300. - p.y, 800, 600);
//        ui->ui->Gameview->setSceneRect(p.x - 400., -300. - p.y, 800, 600);
//        std::cout << "Unit : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
    }
    for (std::list<GameData::Physics>::iterator it = pbullet.begin(); it != pbullet.end(); it++) {
        p = *it;
        QPolygon *poly = new QPolygon();
        for (std::list<GameData::Physics::Coord>::iterator ite = p.vertices.begin(); ite != p.vertices.end(); ite++) {
            c = *ite;
            (*poly) << QPoint(c.x, c.y * -1);
            //            std::cout << c.x << " " << c.y << std::endl;
        }
        item = scene->addPolygon(*poly);
        //        std::cout << "Bullet : " << p.x << " " << p.y << std::endl;
        item->setPos(p.x * 1, p.y * -1);
    }
    view->setScene(scene);
    view->show();
//    ui->ui->Gameview->setScene(scene);
//    ui->ui->Gameview->show();
}
