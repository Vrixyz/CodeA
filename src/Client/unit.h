#ifndef UNIT_H
#define UNIT_H

#include "game.h"

class Unit : public QGraphicsItem
{
public:
    Unit(GameData::Unit, GameData::Physics, QGraphicsScene *);
    ~Unit();
    void Draw();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    GameData::Unit unit;
    GameData::Physics physics;
    QGraphicsScene *scene;
    QRectF bound;
    bool exist;
    int type() const;
    enum {
        Type = UserType + 3
    };
};

#endif // UNIT_H
