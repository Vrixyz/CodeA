//
// Object.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 11:04:47 2012 thierry berger
// Last update Wed Sep 12 13:24:31 2012 mathieu leurquin
//

#ifndef SERVER_OBJECT_HPP
# define SERVER_OBJECT_HPP

#include "World.hpp"

namespace Server
{
  class	Object
  {
    typedef enum e_Type 
      {
	Unit,
	Element
      } Type;
    Type getType() const {return _type}
    void die() = 0;

  protected:
    Object(World& world, Type type) : _type(t), _world(world){}
    Type _type;
    World& _world;
  };
}

#endif
