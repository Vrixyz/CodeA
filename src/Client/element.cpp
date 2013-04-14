#include "element.h"

Element::Element(GameData::Element _elem, GameData::Physics _physics, QGraphicsScene *_scene) : elem(_elem), physics(_physics), scene(_scene), exist(true)
{
}

Element::~Element()
{
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    option = option;
    widget = widget;
    painter->drawEllipse(QPointF(physics.x, physics.y * -1), 25, 25);
//    QPolygonF poly;
//    GameData::Physics::Coord c;
//    for (std::list<GameData::Physics::Coord>::iterator ite = physics.vertices.begin(); ite != physics.vertices.end(); ite++) {
//        c = *ite;
//        poly << QPoint(c.x, c.y * -1);
//    }
    bound = QRectF((physics.x - 25), (physics.y + 25) * -1, 50, 50);
//    this->setRotation(physics.angle);
//    this->setPos(physics.x * 1, physics.y * -1);
//    painter->drawPolygon(poly);
    update(bound);
}

void Element::Draw()
{
    scene->addItem(this);
}

QRectF Element::boundingRect() const
{
    return (bound);
}

int Element::type() const
{
    return Type;
}

