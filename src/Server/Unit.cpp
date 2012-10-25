//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Thu Oct 25 13:59:12 2012 mathieu leurquin
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
  _data.playersId.push_back(p->id);
}

bool	Server::Unit::ownPlayer(int idPlayer)
{
   for (std::list<uint32_t>::iterator it = _data.playersId.begin(); it != _data.playersId.end(); it++)
    {
      if ((*it) == idPlayer)
	return true;
      return false;
    }
   return false;
}

void	Server::Unit::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}

// void	Server::Unit::goUp()
// {
//   if (direction.get(1) == 0)
//     {
//       b2Vec2 vel = _body->GetLinearVelocity();
//       float desiredVel = 5;
//       float velChange = desiredVel - vel.y;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
//       direction.set(1);
//     }
// }

// void	Server::Unit::goRight()
// {
//   if (direction.get(2) == 0)
//     {
//       b2Vec2 vel = _body->GetLinearVelocity();
//       float desiredVel = 5;
//       float velChange = desiredVel - vel.x;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
//       direction.set(2);
//     }
// }

// void	Server::Unit::goDown()
// {
//   if (direction.get(3) == 0)
//     {
//       b2Vec2 vel = _body->GetLinearVelocity();
//       float desiredVel = -5;
//       float velChange = desiredVel - vel.y;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
//       direction.set(3);
//     }
// }
// void Server::Unit::goLeft()
// {
//   if (direction.get(4) == 0)
//     {
//       b2Vec2 vel = _body->GetLinearVelocity();
//       float desiredVel = 5;
//       float velChange = desiredVel - vel.x;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
//       direction.set(4);
//     }
// }

// void Server::Unit::stopUp()
// {
//   if (direction.get(1) == 1)
//     {
//       b2Vec2 vel = _body->GetLinearVelocity();
//       float desiredVel = 0;
//       float velChange = desiredVel - 5;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
//       direction.unset(1);
//     }
// }

// void Server::Unit::stopRight()
// {
//   if (direction.get(2) == 1)
//     {
//       float desiredVel = 0;
//       float velChange = desiredVel - 5;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
//       direction.unset(2);
//     }
// }

// void Server::Unit::stopDown()
// {
//   if (direction.get(3) == 1)
//     {
//       float desiredVel = 0;
//       float velChange = desiredVel - 5;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(0, impulse), _body->GetWorldCenter());
//       direction.unset(3);
//     }
// }

// void Server::Unit::stopLeft()
// {
//   if (direction.get(4) == 1)
//     {
//       float desiredVel = 0;
//       float velChange = desiredVel - 5;
//       float impulse = _body->GetMass() * velChange;
      
//       _body->ApplyLinearImpulse(b2Vec2(impulse, 0), _body->GetWorldCenter());
//       direction.unset(4);
//     }
// }

void Server::Unit::move(float x, float y)
{
  current.x = x - current.x;
  current.y = y - current.y;
  float impulseX = _body->GetMass() * current.x;
  float impulseY = _body->GetMass() * current.y;

  _body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), _body->GetWorldCenter());
  std::cout<<"Move"<<std::endl;
}

void Server::Unit::fire(float x, float y)
{
}

void Server::Unit::aimTo(float x, float y)
{
}

void Server::Unit::moveTo(float x, float y)
{
}

