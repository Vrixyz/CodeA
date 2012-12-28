//
// Element.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 17:53:20 2012 thierry berger
// Last update Wed Dec 12 12:28:20 2012 mathieu leurquin
//

#include "Element.hpp"

b2Body*	Server::Element::setBody(BitField *b, float width, float height, int x, int y)
{
  b2BodyDef eBDef;

  eBDef.userData = this;
  eBDef.fixedRotation = true;
  eBDef.type = b2_staticBody;
  eBDef.gravityScale = 0;
  // NOTE: if you place an element on top of the other, valgrind dislikes.
  eBDef.position.Set(x, y);
  this->_body = _world._physicWorld.CreateBody(&eBDef);

  b2PolygonShape elementShape;
  elementShape.SetAsBox(width, height);

  b2FixtureDef fDef;
  fDef.shape = &elementShape;

  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;

  // fDef.filter.categoryBits = -1;
  // fDef.filter.maskBits = -1;

  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void Server::Element::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
  packet.pack(this->getPhysics());
}

bool Server::Element::unSerialize(msgpack::packer<msgpack::sbuffer>& packet)
{
  return false;
}

int	Server::Element::getClassId() const
{
  return 0;
}

Server::Element::~Element()
{
  _body->GetWorld()->DestroyBody(_body);
}

void Server::Element::intraCollision(Object *o)
{
  if (o->getType() == Object::Element)
    this->intraCollisionElement(o);
  else if(o->getType() == Object::Bullet)
    this->intraCollisionBullet(o);
  else if(o->getType() == Object::Unit)
    this->intraCollisionUnit(o);
}

void Server::Element::intraCollisionUnit(Object *o)
{
  std::cout<<"element::Collision with a Element and Unit!"<<std::endl;
}

void Server::Element::intraCollisionElement(Object *o)
{
  std::cout<<"elemtn::Collision with a element and Element!"<<std::endl;
}

void Server::Element::intraCollisionBullet(Object *o)
{
  std::cout<<"element::Collision with a element and Bullet!"<<std::endl;
}
