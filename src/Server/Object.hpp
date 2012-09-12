//
// Object.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 11:04:47 2012 thierry berger
// Last update Wed Sep 12 18:22:45 2012 thierry berger
//

#ifndef SERVER_OBJECT_HPP
# define SERVER_OBJECT_HPP

#include "../GameData/Serializable.hpp"

namespace Server
{
  class World;
  /// To keep for the contactListener to know which type is colliding
  class	Object : public GameData::Serializable
  {
  public:
    typedef enum e_Type 
      {
	Unit,
	Element,
	Bullet,
	Player
      } Type;
    Type getType() const {return _type;}
    // void die() = 0;
    /// do a method contact(Unit) / contact(Element) / etc...

  protected:
    Object(World& world, Type type) : _type(type), _world(world){}
    Type _type; /// put that in Serializable
    World& _world;
  };
}

#include "World.hpp"

#endif
