//
// Bullet.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Fri Sep 14 10:40:12 2012 thierry berger
// Last update Fri Sep 14 11:04:57 2012 thierry berger
//

#include "Bullet.hpp"

b2Body*	Server::Bullet::setBody()
{
  b2BodyDef bBDef;

  bBDef.userData = this;
  bBDef.fixedRotation = true;
  bBDef.bullet = true;
  bBDef.type = b2_dynamicBody;
  bBDef.gravityScale = 0;
  this->_body = _world._physicWorld.CreateBody(&bBDef);

  b2PolygonShape bulletShape;
  bulletShape.SetAsBox(0.5, 0.5);

  b2FixtureDef fDef;
  fDef.shape = &bulletShape;
  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void	Server::Bullet::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}
