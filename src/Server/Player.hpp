//
// Player.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:20:38 2012 mathieu leurquin
// Last update Thu Mar  7 10:31:10 2013 mathieu leurquin
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
    typedef enum s_race 
      {
	Mage = 0,
	Minion = 1
      }race;
    int id;
    int score;
    float time;
    race type;

    Player(int playerId, race t) : id(playerId), type(t) 
    {
      time = 0;
      score = 0;
    }
    virtual ~Player() {}

    virtual void* serialize(int& finalLength) const {return 0;};
    virtual int	getClassId() const {return 0;}
  };
}

#endif
