//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Tue Sep 18 10:33:44 2012 mathieu leurquin
//

#include "Unit.hpp"
#define SET(flag, bit) ((flag) |= (1 << (bit)))
#define CLEAR(flag, bit) ((flag) &= ~(1 << (bit)))

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
  for (std::list<uint32_t>::iterator it = _data.playersId.begin(); it != _data.playersId.end(); it++)
    {
      if ((*it) == p->id)
	return;
      _data.playersId.push_back(p->id);
    }
}

void	Server::Unit::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}

void	Server::Unit::goUp()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 5;
  float velChange = desiredVel - vel.y;
  float impulse = _body->GetMass() * velChange;

  _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
  SET(direction, 1);
}

void	Server::Unit::goRight()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 5;
  float velChange = desiredVel - vel.x;
  float impulse = _body->GetMass() * velChange;
  
  _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
  SET(direction, 2);
}

void	Server::Unit::goDown()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = -5;
  float velChange = desiredVel - vel.y;
  float impulse = _body->GetMass() * velChange;

  _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
  SET(direction, 3);
}

void Server::Unit::goLeft()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 5;
  float velChange = desiredVel - vel.x;
  float impulse = _body->GetMass() * velChange;
  
  _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
  SET(direction, 4);
}

void Server::Unit::stopUp()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 0;
  float velChange = desiredVel - vel.y;
  float impulse = _body->GetMass() * velChange;

  _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
  CLEAR(direction, 1);
}

void Server::Unit::stopRight()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 0;
  float velChange = desiredVel - vel.x;
  float impulse = _body->GetMass() * velChange;
  
  _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
  CLEAR(direction, 2);
}

void Server::Unit::stopDown()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 0;
  float velChange = desiredVel - vel.y;
  float impulse = _body->GetMass() * velChange;

  _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
  CLEAR(direction, 3);
}

void Server::Unit::stopLeft()
{
  b2Vec2 vel = _body->GetLinearVelocity();
  float desiredVel = 0;
  float velChange = desiredVel - vel.x;
  float impulse = _body->GetMass() * velChange;
  
  _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
  CLEAR(direction, 4);
}
