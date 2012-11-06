//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Tue Nov  6 10:52:33 2012 mathieu leurquin
//

#include "Unit.hpp"

b2Body*	Server::Unit::setBody(BitField *b)
{
  b2BodyDef uBDef;

  uBDef.userData = this;
  uBDef.fixedRotation = true;
  uBDef.type = b2_dynamicBody;
  uBDef.gravityScale = 0;
  uBDef.bullet = true;
  uBDef.position.Set(0, 0);  
  this->_body = _world._physicWorld.CreateBody(&uBDef);
  b2PolygonShape unitShape;
  unitShape.SetAsBox(2, 2);
  
  b2FixtureDef fDef;
  fDef.shape = &unitShape;
  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;
  this->_body->CreateFixture(&fDef);

  //collision
  // std::string *s = new std::string("mage");
  // this->_body->SetUserData((void*)s);

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

void Server::Unit::askMove(float x, float y)
{
  std::cout<<"Move " << x << ";" << y <<std::endl;
  current.x = x;
  current.y = y;
}

void Server::Unit::move(float x, float y)
{
  float impulseX = _body->GetMass() * x;
  float impulseY = _body->GetMass() * y;
  float im;
  float im1;
  b2Vec2 actualLinearVelocity;

  actualLinearVelocity = _body->GetLinearVelocity();
  if (x == 0 && y == 0)
    {
      if (actualLinearVelocity.y != 0 && actualLinearVelocity.x != 0)
	{
	  im = 0 - actualLinearVelocity.x;
	  im1 = 0 - actualLinearVelocity.y;
	  _body->ApplyLinearImpulse(b2Vec2(im, im1), _body->GetWorldCenter());
	}
      if (actualLinearVelocity.y != 0)
	{
	  im = 0 - actualLinearVelocity.y;
	  _body->ApplyLinearImpulse(b2Vec2(0, im), _body->GetWorldCenter());
	}
      else if (actualLinearVelocity.x != 0)
	{
	  im = 0 - actualLinearVelocity.x;
	  _body->ApplyLinearImpulse(b2Vec2(im, 0), _body->GetWorldCenter());
	}
    }
  _body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), _body->GetWorldCenter());
  // std::cout<<"Move" << impulseX << ";" << impulseY <<std::endl;
}

void Server::Unit::update(float elapsedMilliseconds)
{
  // b2Vec2 curVel = _body->GetLinearVelocity();
  // if (curVel.x != current.x && curVel.y != current.y)
    this->move(current.x, current.y);
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

void Server::Unit::shield(float x, float y)
{
  BitField *shield = new BitField(Server::BitField::SHIELD_MAGE, Server::BitField::OBSTACLE);
  Server::Element *e = new Server::Element(this->_world, (int)this->_world.elements.size(), false);
  b2Vec2 position = this->getBody()->GetPosition();
  
  e->setBody(shield, 1, 10, position.x + 10, position.y + 1);
  _world.elements.push_back(e); 
}

void Server::Unit::rotateLeft()
{
  float impulse = body->GetInertia() * (-10);// disregard time factor
 
  this->getBody()->ApplyAngularImpulse(impulse);
}

void Server::Unit::rotateRight()
{
  float impulse = body->GetInertia() * (-10);// disregard time factor
 
  this->getBody()->ApplyAngularImpulse(impulse);
}
 
void Server::Unit::rotateStop()
{
  float impulse = 0;
 
  this->getBody()->ApplyAngularImpulse(impulse);
}
