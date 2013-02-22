//
// Portal.cpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Thu Feb 21 10:56:20 2013 mathieu leurquin
// Last update Fri Feb 22 12:35:55 2013 mathieu leurquin
//

#include "World.hpp"
#include "Portal.hpp"

b2Body*	Server::Portal::setBody(BitField *b, float x, float y)
{
  b2BodyDef uBDef;

  uBDef.type = b2_staticBody;
  uBDef.userData = this;
  uBDef.fixedRotation = true;
  uBDef.gravityScale = 0;
  uBDef.bullet = true;
  // NOTE: if you place an element on top of the other, valgrind dislikes.
  uBDef.position.Set(x, y);  
  this->_body = _world._physicWorld.CreateBody(&uBDef);
  b2PolygonShape unitShape;
  unitShape.SetAsBox(10, 10);
  
  b2FixtureDef fDef;
  fDef.shape = &unitShape;

  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;

  // fDef.filter.categoryBits = -1;
  // fDef.filter.maskBits = -1;
  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void	Server::Portal::addPlayer(Player* p)
{
  _data.playersId.push_back(p->id);
}

bool	Server::Portal::belongsToPlayer(int idPlayer) const
{
   for (std::list<uint32_t>::const_iterator it = _data.playersId.begin(); it != _data.playersId.end(); it++)
    {
      if ((*it) == idPlayer)
	return true;
      return false;
    }
   return false;
}

void	Server::Portal::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
  packet.pack(this->getPhysics());
}


void Server::Portal::setMove(const GameData::CommandStruct::Move& arg)
{
}

void Server::Portal::setRotateLeft()
{
}

void Server::Portal::setRotateRight()
{
}

void Server::Portal::setRotateStop()
{
}

void Server::Portal::spell1(const GameData::CommandStruct::Fire &arg)
{
}

void Server::Portal::spell2(const GameData::CommandStruct::Shield arg)
{
}


void Server::Portal::createMinion()
{
  BitField *b;

  if (_world.players.size() == 1)
    b = new  BitField(Server::BitField::TEAM1_UNIT, Server::BitField::TEAM2_BULLET | Server::BitField::TEAM2_UNIT | Server::BitField::OBSTACLE | Server::BitField::PORTAL);
  else
    b = new  BitField(Server::BitField::TEAM2_UNIT, Server::BitField::TEAM1_BULLET | Server::BitField::TEAM1_UNIT | Server::BitField::OBSTACLE | Server::BitField::PORTAL | Server::BitField::TEAM2_UNIT);

  b2Vec2 position = this->getBody()->GetPosition();
  if (belongsToPlayer(0) == true)
    this->_world.createMinion(b, _world.players.front(), position.x, position.y);
  else
    this->_world.createMinion(b, _world.players.back(), position.x, position.y);
}

void Server::Portal::update(float elapsedMilliseconds)
{
  if (_data.health <= 0)
    {
      _world.addPlayerToDestroy(this);
      return;
    }
  pop += elapsedMilliseconds;
  
  if (pop >= 10000)
    {
      this->createMinion();
      pop = 0;
    }
}

void Server::Portal::intraCollision(Object *o)
{
  if (o->getType() == Object::Element)
    this->intraCollisionElement(o);
  else if(o->getType() == Object::Bullet)
    this->intraCollisionBullet(o);
  else if(o->getType() == Object::Unit)
    this->intraCollisionUnit(o);
}

void Server::Portal::intraCollisionUnit(Object *o)
{
  std::cout<<"Unit:!:Collision with a unit and unit!"<<std::endl;
}

void Server::Portal::intraCollisionElement(Object *o)
{
  std::cout<<"Unit::Collision with a unit and element!"<<std::endl;
}

void Server::Portal::intraCollisionBullet(Object *o)
{
  _data.health -= 2;
  std::cout<<"Unit::Collision with a unit and bullet!"<<std::endl;
}
