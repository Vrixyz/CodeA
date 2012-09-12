//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Wed Sep 12 13:14:08 2012 mathieu leurquin
//

#ifndef SERVER_WORLD_HPP
# define SERVER_WORLD_HPP

#include <Box2D/Box2D.h>
#include "../GameData/World.hpp"

namespace Server
{
  class	World
  {
    List<b2Body>	objects;
    GameData::World	data;
  };
}

#endif
