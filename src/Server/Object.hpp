//
// Object.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 11:04:47 2012 thierry berger
// Last update Sun Oct 28 12:08:47 2012 thierry berger
//

#ifndef SERVER_OBJECT_HPP
# define SERVER_OBJECT_HPP

#include <Box2D/Box2D.h>
#include "../GameData/Serializable.hpp"
#include "../GameData/Physics.hpp"

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
      } Type;
    const int id;

    Type getType() const {return _type;}
    // void die() = 0;
    /// TODO: a method contact(Unit) / contact(Element) / etc...

  protected:
    Type _type; /// put that in Serializable
    World& _world;
    b2Body* _body;
    GameData::Physics getPhysics() const;
    Object(World& world, Type type, int _id) : id(_id), _type(type), _world(world){}
  };
}

#include "World.hpp"

#endif
