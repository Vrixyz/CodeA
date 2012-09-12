//
// Unit.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:00:00 2012 mathieu leurquin
// Last update Wed Sep 12 13:24:31 2012 mathieu leurquin
//

#ifndef SERVER_UNIT_HPP
# define SERVER_UNIT_HPP

#include "../GameData/Unit.hpp"
#include "Object.hpp"

namespace Server
{
  class	Unit : public Object
  {
  public:
    GameData::Unit _data;
    
    GameData::Unit getData();
    
    void fire(float x, float y);
    void aimTo(float x, float y);
    void moveTo(float x, float y);
    void startMoving();
    void stopMoving();
    void goUp();
    void goRight();
    void goDown();
    void goLeft();
    void stopUp();
    void stopRight();
    void stopDown();
    void stopLeft();
  };
}

#endif
