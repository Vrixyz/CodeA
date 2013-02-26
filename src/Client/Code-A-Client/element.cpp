#include "element.h"

Element::Element(int _id, float _x, float _y, float _angle, std::list<GameData::Physics::Coord> _vertices) : id(_id), x(_x), y(_y), angle(_angle), vertices(_vertices)
{

}
