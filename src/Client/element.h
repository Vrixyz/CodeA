#ifndef ELEMENT_H
#define ELEMENT_H

#include "game.h"

class Element : public QGraphicsItem
{
public:
    Element(GameData::Element , GameData::Physics, QGraphicsScene *);
    void Draw();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    GameData::Element elem;
    GameData::Physics physics;
    QGraphicsScene *scene;
    QRectF bound;
    int type() const;
    enum {
        Type = UserType + 2
    };
};

#endif // ELEMENT_H
