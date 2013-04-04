#include "bullet.h"

Bullet::Bullet(GameData::Bullet _bullet, GameData::Physics _physics, QGraphicsScene *_scene) : bullet(_bullet), physics(_physics), scene(_scene)
{
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(physics.x, physics.y * -1, 5, 5);
}

void Bullet::Draw()
{
    scene->addItem(this);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(physics.x, physics.y * -1, 5, 5);
}

int Bullet::type() const
{
    return Type;
}
