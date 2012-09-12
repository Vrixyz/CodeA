//
// Player.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:20:38 2012 mathieu leurquin
// Last update Wed Sep 12 18:20:07 2012 thierry berger
//

#ifndef SERVER_PLAYER_HPP
# define SERVER_PLAYER_HPP

#include <list>
#include <Box2D/Box2D.h>

#include "../GameData/Unit.hpp"
#include "Object.hpp"
#include "World.hpp"

namespace Server
{
  class	Player : public Object
  {
  public:
    int id;

    std::list<b2Body*> units;

    Player(World& world, int playerId) : Object(world, Object::Player), id(playerId) {}
    b2Body&	addUnit(b2Body& unit);

    virtual void* serialize(int& finalLength) const {return 0;};
    virtual int	getClassId() const {return 0;}
  };
}

#endif
