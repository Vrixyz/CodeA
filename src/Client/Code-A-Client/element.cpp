#include "element.h"

Element::Element(GameData::Element _elem, GameData::Physics _physics) : elem(_elem), physics(_physics), QGraphicsItem(NULL, _scene)
{

}
