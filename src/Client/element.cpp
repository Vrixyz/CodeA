#include "element.h"

Element::Element(GameData::Element _elem, GameData::Physics _physics, QGraphicsScene *_scene) : elem(_elem), physics(_physics), scene(_scene)
{
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPolygonF poly;
//    GameData::Physics::Coord c;
//    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
//        c = *ite;
//        poly << QPoint(c.x, c.y * -1);
//    }
//    bound = poly.boundingRect();
//    this->setRotation(physics.angle);
//    this->setPos(physics.x * 1, physics.y * -1);
//    painter->drawPolygon(poly);
}

void Element::Draw()
{
    QGraphicsItem *item;
    QPolygonF poly;
    GameData::Physics::Coord c;
    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
        c = *ite;
        poly << QPoint(c.x, c.y * -1);
    }
    item = scene->addPolygon(poly);
    item->setRotation(physics.angle);
    item->setPos(physics.x * 1, physics.y * -1);
//    scene->addItem(this);
}

QRectF Element::boundingRect() const
{
    return (bound);
}
