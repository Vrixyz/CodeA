//
// Element.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 17:53:20 2012 thierry berger
// Last update Mon Nov  5 11:00:02 2012 mathieu leurquin
//

#include "Element.hpp"

b2Body*	Server::Element::setBody(BitField *b, float width, float height, int x, int y)
{
  b2BodyDef eBDef;

  eBDef.userData = this;
  eBDef.fixedRotation = true;
  eBDef.type = b2_staticBody;
  eBDef.gravityScale = 0;
  eBDef.position.Set(x, y);
  this->_body = _world._physicWorld.CreateBody(&eBDef);

  b2PolygonShape elementShape;
  elementShape.SetAsBox(width, height);

  b2FixtureDef fDef;
  fDef.shape = &elementShape;
  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;
  this->_body->CreateFixture(&fDef);
  
  //collision
  // std::string *s = new std::string("element");
  // this->_body->SetUserData((void*)s);


  return this->_body;
}

void Server::Element::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}

bool Server::Element::unSerialize(msgpack::packer<msgpack::sbuffer>& packet)
{
  return false;
}

int	Server::Element::getClassId() const
{
  return 0;
}
