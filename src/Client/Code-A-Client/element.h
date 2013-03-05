#ifndef ELEMENT_H
#define ELEMENT_H

#include "game.h"

class Element : public QPolygonF
{
public:
    Element(GameData::Element , GameData::Physics, QGraphicsScene *);
    GameData::Element elem;
    GameData::Physics physics;
    QGraphicsScene *scene;
};

#endif // ELEMENT_H
