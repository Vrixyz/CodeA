//
// Player.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:20:38 2012 mathieu leurquin
// Last update Fri Feb 22 12:38:06 2013 mathieu leurquin
//

#ifndef SERVER_PLAYER_HPP
# define SERVER_PLAYER_HPP

#include <list>
#include <Box2D/Box2D.h>

namespace Server
{
  class	Player
  {
  public:
    int id;
    int score;
    Player(int playerId) : id(playerId) 
    {
      score = 0;
    }
    virtual ~Player() {}

    virtual void* serialize(int& finalLength) const {return 0;};
    virtual int	getClassId() const {return 0;}
  };
}

#endif
