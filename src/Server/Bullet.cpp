//
// Bullet.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Fri Sep 14 10:40:12 2012 thierry berger
// Last update Wed Nov 14 17:04:20 2012 mathieu leurquin
//

#include "Bullet.hpp"

b2Body*	Server::Bullet::setBody(float angle, b2Vec2 position)
{
  b2BodyDef bBDef;

  bBDef.userData = this;
  bBDef.fixedRotation = true;
  bBDef.bullet = true;
  bBDef.type = b2_dynamicBody;
  bBDef.gravityScale = 0;
  bBDef.angle = angle;
  bBDef.position.Set(position.x + 1, position.y + 1);
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
  packet.pack(this->getPhysics());
}
