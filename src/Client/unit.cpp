#include "unit.h"

Unit::Unit(GameData::Unit _unit, GameData::Physics _physics, QGraphicsScene *_scene) : unit(_unit), physics(_physics), scene(_scene)
{
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygonF poly;
    GameData::Physics::Coord c;
    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
        c = *ite;
        poly << QPoint(c.x, c.y * -1);
    }
    bound = poly.boundingRect();
    this->setRotation(physics.angle);
    this->setPos(physics.x * 1, physics.y * -1);
    painter->drawPolygon(poly);
//    std::cout << "painting" << std::endl;
}

void Unit::Draw()
{
//    QPolygonF poly;
//    GameData::Physics::Coord c;
//    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
//        c = *ite;
//        poly << QPoint(c.x, c.y * -1);
//    }
//    QGraphicsItem *item;
//    item = scene->addPolygon(poly);
//    item->setRotation(physics.angle);
//    item->setPos(physics.x * 1, physics.y * -1);
    scene->addItem(this);
}

QRectF Unit::boundingRect() const
{
    return (bound);
}

int Unit::type() const
{
    return Type;
}
