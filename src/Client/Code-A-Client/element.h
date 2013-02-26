#ifndef ELEMENT_H
#define ELEMENT_H

#include "mainwindow.h"

class Element : public QObject
{
public:
    Element(int, float, float, float, std::list<GameData::Physics::Coord> );
    unsigned int id;
    float	x;
    float	y;
    float	angle;
    std::list<GameData::Physics::Coord> vertices;
};

#endif // ELEMENT_H
