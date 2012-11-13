//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Fri Nov  9 13:37:24 2012 mathieu leurquin
//

#include "Unit.hpp"

b2Body*	Server::Unit::setBody(BitField *b)
{
  b2BodyDef uBDef;

  uBDef.type = b2_dynamicBody;
  uBDef.userData = this;
  uBDef.fixedRotation = false;
  uBDef.type = b2_dynamicBody;
  uBDef.gravityScale = 0;
  uBDef.bullet = true;
  // NOTE: if you place an element on top of the other, valgrind dislikes.
  uBDef.position.Set(0, 0);  
  this->_body = _world._physicWorld.CreateBody(&uBDef);
  b2PolygonShape unitShape;
  unitShape.SetAsBox(5, 5);
  
  b2FixtureDef fDef;
  fDef.shape = &unitShape;
  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;
  // fDef.filter.categoryBits = -1;
  // fDef.filter.maskBits = -1;
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
  packet.pack(this->getPhysics());
}

void Server::Unit::move(int x, int y)
{
  float impulseX;
  float impulseY;
  b2Vec2 actualLinearVelocity;

  actualLinearVelocity = _body->GetLinearVelocity();
  impulseX = _body->GetMass() * x - actualLinearVelocity.x;
  impulseY = _body->GetMass() * y - actualLinearVelocity.y;

  // std::cout<<"actualLinealVelocity: " <<  actualLinearVelocity.x << ";" << actualLinearVelocity.y << std::endl;
  _body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), _body->GetWorldCenter());
  // std::cout<<"Move" << impulseX << ";" << impulseY <<std::endl;
  actualLinearVelocity = _body->GetLinearVelocity();
  // std::cout<<"actualLinealVelocity: " <<  actualLinearVelocity.x << ";" << actualLinearVelocity.y << std::endl;
}

void Server::Unit::askMove(int idPlayer, int x, int y)
{
  if (this->ownPlayer(idPlayer))
    {
      current.x = x;
      current.y = y;
    }
}

void Server::Unit::askRotateLeft(int idPlayer)
{
  if (this->ownPlayer(idPlayer))
    {
      rotation = -0.001;
    }
}

void Server::Unit::askRotateRight(int idPlayer)
{
  if (this->ownPlayer(idPlayer))
    {
      rotation = 0.001;
    }
}

void Server::Unit::askRotateStop(int idPlayer)
{
  if (this->ownPlayer(idPlayer))
    {
      rotation = 0;
    }
}



void Server::Unit::update(float elapsedMilliseconds)
{
  // b2Vec2 curVel = _body->GetLinearVelocity();
  // if (curVel.x != current.x && curVel.y != current.y)
  this->move(current.x, current.y);
  _body->SetAngularVelocity(rotation);
}
