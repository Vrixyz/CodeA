//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Fri Sep 14 10:35:57 2012 thierry berger
//

#include "Unit.hpp"

b2Body*	Server::Unit::setBody()
{
  b2BodyDef uBDef;

  uBDef.userData = this;
  uBDef.fixedRotation = true;
  uBDef.type = b2_dynamicBody;
  uBDef.gravityScale = 0;
  this->_body = _world._physicWorld.CreateBody(&uBDef);
  b2PolygonShape unitShape;
  unitShape.SetAsBox(2, 2);
  b2FixtureDef fDef;
  fDef.shape = &unitShape;
  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void	Server::Unit::addPlayer(Player* p)
{
  /// TODO: add only if not already in the list
  _data.playersId.push_back(p->id);
}

void Server::Unit::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}
