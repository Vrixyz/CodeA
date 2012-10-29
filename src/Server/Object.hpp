//
// Object.hpp for  in /home/leurqu_m//Documents/tek3/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Mon Oct 29 16:47:27 2012 mathieu leurquin
// Last update Mon Oct 29 16:47:31 2012 mathieu leurquin
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
  public:   
    b2Body* getBody(){return _body;}
  };
}

#include "World.hpp"

#endif
