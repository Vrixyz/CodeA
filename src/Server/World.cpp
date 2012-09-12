//
// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Wed Sep 12 17:53:04 2012 thierry berger
//

#include "World.hpp"

void	Server::World::init()
{
  this->createPlayer(4).addUnit(this->createUnit());
  this->createElement(true, 100, 100);
}

void	Server::World::run()
{
  
}

Server::Player&	Server::World::createPlayer(int id)
{
  Player* p = new Player(*this, id);

  players.push_back(p);
  return *p;
}

b2Body&	Server::World::createUnit()
{
  Server::Unit* u = new Server::Unit(*this, (int)units.size());
  b2BodyDef uBDef;
  b2Body* physicBody;

  uBDef.userData = u;
  uBDef.fixedRotation = true;
  uBDef.type = b2_dynamicBody;
  uBDef.gravityScale = 0;
  physicBody = _physicWorld.CreateBody(&uBDef);

  b2PolygonShape unitShape;
  unitShape.SetAsBox(2, 2);

  b2FixtureDef fDef;
  fDef.shape = &unitShape;
  physicBody->CreateFixture(&fDef);
  units.push_back(physicBody);
  return *physicBody;
}

b2Body& Server::World::createElement(bool walkable, int width, int height)
{
  Element* e = new Element(*this, (int)elements.size(), walkable);
  b2BodyDef eBDef;
  b2Body* physicBody;

  eBDef.userData = e;
  eBDef.fixedRotation = true;
  eBDef.type = b2_dynamicBody;
  eBDef.gravityScale = 0;
  physicBody = _physicWorld.CreateBody(&eBDef);

  b2PolygonShape elementShape;
  elementShape.SetAsBox(width, height);

  b2FixtureDef fDef;
  fDef.shape = &elementShape;
  physicBody->CreateFixture(&fDef);
  elements.push_back(physicBody);  
  return *physicBody;
}

b2Body&  Server::World::createBullet(int damage)
{
  Bullet* e = new Bullet(*this, damage);
  b2BodyDef eBDef;
  b2Body* physicBody;

  eBDef.userData = e;
  eBDef.fixedRotation = true;
  eBDef.bullet = true;
  eBDef.type = b2_dynamicBody;
  eBDef.gravityScale = 0;
  physicBody = _physicWorld.CreateBody(&eBDef);

  b2PolygonShape elementShape;
  elementShape.SetAsBox(0.5, 0.5);

  b2FixtureDef fDef;
  fDef.shape = &elementShape;
  physicBody->CreateFixture(&fDef);
  elements.push_back(physicBody);  
  return *physicBody;
}
