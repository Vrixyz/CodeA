#include "bullet.h"

Bullet::Bullet(GameData::Bullet _bullet, GameData::Physics _physics, QGraphicsScene *_scene) : bullet(_bullet), physics(_physics), scene(_scene), exist(true)
{
}

Bullet::~Bullet()
{
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(physics.x, physics.y * -1, 5, 5);
    option = option;
    widget = widget;
    bound = QRectF(physics.x, physics.y * -1, 5, 5);
    update(bound);
}

void Bullet::Draw()
{
    scene->addItem(this);
}

QRectF Bullet::boundingRect() const
{
    return (bound);
}

int Bullet::type() const
{
    return Type;
}
