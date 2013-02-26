#include "IUnit.hpp"

static unsigned int _incr_id = 0;

Server::IUnit::IUnit(World& w) : Object(w, Object::Unit, _incr_id), _data(_incr_id, 5) // default is 5 hp, changeable.
{
  _incr_id++;
}
