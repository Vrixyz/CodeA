//
// Object.hpp for  in /home/leurqu_m//Documents/tek3/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Mon Oct 29 16:47:27 2012 mathieu leurquin
// Last update Thu Feb 21 16:09:30 2013 mathieu leurquin
//

#ifndef SERVER_OBJECT_HPP
# define SERVER_OBJECT_HPP

#include <Box2D/Box2D.h>
#include "../GameData/Serializable.hpp"
#include "../GameData/Physics.hpp"
#include <iostream>

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
	Bullet
      } Type;
    const int id;

    Type getType() const {return _type;}
    // void die() = 0;

    virtual void update(float) {};

    b2Body* getBody(){return _body;}
    void collision(Object *o)
    {
      intraCollision(o);
      o->intraCollision(this);
    }

    virtual ~Object() {} // we should delete the body here.

  protected:
    Type _type; /// put that in Serializable
    World& _world;
    b2Body* _body;
    std::map<Type, void (Server::Object::*)(Server::Object *o)> intraCollisionTab;
    GameData::Physics getPhysics() const;
    Object(World& world, Type type, int _id) : id(_id), _type(type), _world(world)
    {
      // intraCollisionTab[Unit] = &Object::intraCollisionUnit;
      // intraCollisionTab[Element] = &Object::intraCollisionElement;
      // intraCollisionTab[Bullet] = &Object::intraCollisionBullet;
    }
    virtual void intraCollision(Object *o)
    {
      if (o->getType() == Element)
	this->intraCollisionElement(o);
      else if(o->getType() == Bullet)
	this->intraCollisionBullet(o);
      else if(o->getType() == Unit)
	this->intraCollisionUnit(o);
	// (*intraCollisionTab[o->getType()])(o);
    }
    
  private:
    
    void intraCollisionUnit(Object *)
    {
      std::cout<<"object::Collision with a object and unit!"<<std::endl;
    }
    
    void intraCollisionBullet(Object *)
    {
      std::cout<<"oecbjt::Collision with a object and bullet!"<<std::endl;
    }
    
    void intraCollisionElement(Object *)
    {
      std::cout<<"object::Collision with a object and element!"<<std::endl;
    }
  };
}

#endif
