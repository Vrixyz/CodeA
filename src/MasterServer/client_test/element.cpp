#include "element.h"

Element::Element(GameData::Element _elem, GameData::Physics _physics, QGraphicsScene *_scene) : QPolygonF(), elem(_elem), physics(_physics), scene(_scene)
{
    QGraphicsItem *item;
    GameData::Physics::Coord c;
    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
        c = *ite;
        *this << QPoint(c.x, c.y * -1);
        //            std::cout << c.x << " " << c.y << std::endl;
    }
    item = scene->addPolygon(this->toPolygon());
    item->setRotation(physics.angle);
//            std::cout << "Elem : " << p.x << " " << p.y << std::endl;
    item->setPos(physics.x * 1, physics.y * -1);
}
