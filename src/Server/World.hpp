//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Wed Sep 12 14:07:41 2012 mathieu leurquin
//

#ifndef SERVER_WORLD_HPP
# define SERVER_WORLD_HPP

#include <Box2D/Box2D.h>
#include "../GameData/World.hpp"
#include "../GameData/Unit.hpp"

#include <list>

namespace Server
{
  class	World
  {
  public:
    std::list<b2Body*>	objects;
    GameData::World	data;

    World(GameData::World d) : data(d){}
    void HandleContact(b2Body object1, b2Body object2);
    b2Body& createUnit(GameData::Unit data);
    b2Body& createElement(GameData::Unit data);
    b2Body& getUnit(int id);
    b2Body& getElement(int id);
  };
}

#endif
