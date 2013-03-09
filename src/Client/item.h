#ifndef ITEM_H
#define ITEM_H

#include "game.h"

class Item
{
public:
    virtual ~Item(){}
    virtual void Draw() = 0;
    GameData::Physics physics;
    QGraphicsScene *scene;
    int t;
};

#endif // ITEM_H
