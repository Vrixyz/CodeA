#include "bullet.h"

Bullet::Bullet(GameData::Bullet _bullet, GameData::Physics _physics, QGraphicsScene *_scene) : bullet(_bullet), physics(_physics), scene(_scene), t(0)
{
}

void Bullet::Draw()
{
    item = scene->addEllipse(physics.x, physics.y * -1, 5, 5);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(physics.x, physics.y * -1, 5, 5);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(physics.x, physics.y, 5, 5);
}
