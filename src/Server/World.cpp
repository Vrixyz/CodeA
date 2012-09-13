//
// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Thu Sep 13 15:42:41 2012 thierry berger
//

#include "World.hpp"

void	Server::World::init()
{
  static_cast<Unit*>(this->createUnit().GetUserData())->addPlayer(&this->createPlayer(4));
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
  Bullet* e = new Bullet(*this, (int)elements.size(), damage);
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

Server::Player* Server::World::getPlayer(int id)
{
  for (std::list<Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
      if ((*it)->id == id)
	{
	  return *it;
	}
      else
	it++;
    }
  return 0;
}

b2Body* Server::World::getUnit(int id)
{
  return getFromList(units, id);
}

b2Body* Server::World::getElement(int id)
{
  return getFromList(elements, id);
}

b2Body* Server::World::getBullet(int id)
{
  return getFromList(bullets, id);
}

void Server::World::destroyPlayer(int id)
{
  for (std::list<Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
      if ((*it)->id == id)
	{
	  delete *it;
	  players.erase(it);
	  return;
	}
      else
	it++;
    }
}

void Server::World::destroyUnit(int id)
{
  return destroyFromList(units, id);
}

void Server::World::destroyBullet(int id)
{
  return destroyFromList(bullets, id);
}

void	Server::World::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(getPhysics(*elements.begin()));
}

bool Server::World::unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}

int	Server::World::getClassId() const {return 0;}


b2Body* Server::World::getFromList(std::list<b2Body*> l, int id)
{
  Object* obj;

  for (std::list<b2Body*>::iterator it = l.begin(); it != l.end(); it++)
    {
      obj = static_cast<Object*>((*it)->GetUserData());
      if (obj->id == id)
	return *it;
    }
  return 0;
}

void Server::World::destroyFromList(std::list<b2Body*> l, int id)
{
  Object* obj;

  for (std::list<b2Body*>::iterator it = l.begin(); it != l.end(); it++)
    {
      obj = static_cast<Object*>((*it)->GetUserData());
      if (obj->id == id)
	{
	  /// TODO: put that in a list to delete later (it may cause problem if deletion in timestep)
	  _physicWorld.DestroyBody(*it);
	  l.erase(it);
	  return;
	}
      else
	it++;
    }
  return;
}

GameData::Physics Server::World::getPhysics(const b2Body* body) const
{
  GameData::Physics physics;
  b2Vec2 position = body->GetPosition();

  physics.x = position.x;
  physics.y = position.y;

  /// assuming that shapes are only simple rectangles (real simple, centered at 0)
  const b2PolygonShape* shape = static_cast<const b2PolygonShape*>(body->GetFixtureList()->GetShape());
  // for (int i = 0; i < 4; ++i)
  //   {
  //     physics.vertices[i][0] = shape->GetVertex(i).x;
  //     physics.vertices[i][1] = shape->GetVertex(i).y;
  //   }
  physics.s0x = shape->GetVertex(0).x;
  physics.s0y = shape->GetVertex(0).y;
  physics.s1x = shape->GetVertex(1).x;
  physics.s1y = shape->GetVertex(1).y;
  physics.s2x = shape->GetVertex(2).x;
  physics.s2y = shape->GetVertex(2).y;
  physics.s3x = shape->GetVertex(3).x;
  physics.s3y = shape->GetVertex(3).y;
  return physics;
}
