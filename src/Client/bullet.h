#ifndef BULLET_H
#define BULLET_H

#include "game.h"

class Bullet : public QGraphicsItem, public Item
{
public:
    Bullet(GameData::Bullet , GameData::Physics, QGraphicsScene *);
    void Draw();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    GameData::Bullet bullet;
    GameData::Physics physics;
    QGraphicsScene *scene;
    QRectF bound;
    int t;
};

#endif // BULLET_H
