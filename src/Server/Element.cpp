//
// Element.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 17:53:20 2012 thierry berger
// Last update Fri Sep 14 10:35:21 2012 thierry berger
//

#include "Element.hpp"

b2Body*	Server::Element::setBody(float width, float height)
{
  b2BodyDef eBDef;

  eBDef.userData = this;
  eBDef.fixedRotation = true;
  eBDef.type = b2_dynamicBody;
  eBDef.gravityScale = 0;
  this->_body = _world._physicWorld.CreateBody(&eBDef);

  b2PolygonShape elementShape;
  elementShape.SetAsBox(width, height);

  b2FixtureDef fDef;
  fDef.shape = &elementShape;
  this->_body->CreateFixture(&fDef);
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
