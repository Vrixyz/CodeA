#ifndef ELEMENT_H
#define ELEMENT_H

#include "game.h"

class Element : public QObject
{
public:
    Element(GameData::Element , GameData::Physics);
    GameData::Element elem;
    GameData::Physics physics;
};

#endif // ELEMENT_H
