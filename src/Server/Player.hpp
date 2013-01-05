//
// Player.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:20:38 2012 mathieu leurquin
// Last update Thu Sep 13 13:29:31 2012 thierry berger
//

#ifndef SERVER_PLAYER_HPP
# define SERVER_PLAYER_HPP

#include <list>
#include <Box2D/Box2D.h>

#include "World.hpp"

namespace Server
{
  class	Player
  {
  public:
    int id;

    Player(World& world, int playerId) : id(playerId) {}
    virtual ~Player() {}

    virtual void* serialize(int& finalLength) const {return 0;};
    virtual int	getClassId() const {return 0;}
  };
}

#endif
