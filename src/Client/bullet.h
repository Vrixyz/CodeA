#ifndef BULLET_H
#define BULLET_H

#include "game.h"

class Bullet : public QGraphicsItem
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
    int type() const;
    enum {
        Type = UserType + 1
    };
};

#endif // BULLET_H
