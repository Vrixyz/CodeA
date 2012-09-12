//
// Player.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:20:38 2012 mathieu leurquin
// Last update Wed Sep 12 13:24:31 2012 mathieu leurquin
//

#ifndef SERVER_PLAYER_HPP
# define SERVER_PLAYER_HPP

#include "../GameData/Unit.hpp"
#include "World.hpp"

namespace Server
{
  class	Player
  {
  public:
    GameData::Unit _data;
  protected:
    World& _world;
  };
}

#endif
