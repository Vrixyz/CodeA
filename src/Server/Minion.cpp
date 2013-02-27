//
// Minion.cpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Fri Feb 22 10:41:33 2013 mathieu leurquin
// Last update Wed Feb 27 10:11:05 2013 mathieu leurquin
//

#include "World.hpp"
#include "Minion.hpp"

b2Body*	Server::Minion::setBody(BitField *b, float x, float y)
{
  b2BodyDef uBDef;

  uBDef.type = b2_dynamicBody;
  uBDef.userData = this;
  uBDef.fixedRotation = true;
  uBDef.type = b2_dynamicBody;
  uBDef.gravityScale = 0;
  uBDef.bullet = true;
  // NOTE: if you place an element on top of the other, valgrind dislikes.
  uBDef.position.Set(x, y);  
  this->_body = _world._physicWorld.CreateBody(&uBDef);
  b2PolygonShape unitShape;
  unitShape.SetAsBox(2, 2);
  
  b2FixtureDef fDef;
  fDef.shape = &unitShape;

  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;

  // fDef.filter.categoryBits = -1;
  // fDef.filter.maskBits = -1;
  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void	Server::Minion::addPlayer(Player* p)
{
  _data.playersId.push_back(p->id);
}

bool	Server::Minion::belongsToPlayer(int idPlayer) const
{
   for (std::list<uint32_t>::const_iterator it = _data.playersId.begin(); it != _data.playersId.end(); it++)
    {
      if ((*it) == idPlayer)
	return true;
      return false;
    }
   return false;
}

void	Server::Minion::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
  packet.pack(this->getPhysics());
}

void Server::Minion::move()
{
  float impulseX;
  float impulseY;
  b2Vec2 actualLinearVelocity;

  actualLinearVelocity = _body->GetLinearVelocity();
  impulseX = _body->GetMass() * current.x - actualLinearVelocity.x;
  impulseY = _body->GetMass() * current.y - actualLinearVelocity.y;

  _body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), _body->GetWorldCenter());
  actualLinearVelocity = _body->GetLinearVelocity();
}

void Server::Minion::setMove(const GameData::CommandStruct::Move& arg)
{
  current.x = arg.x;
  current.y = arg.y;
}

void Server::Minion::setRotateLeft()
{
  rotation = -0.001;
}

void Server::Minion::setRotateRight()
{
  rotation = 0.001;
}

void Server::Minion::setRotateStop()
{
  rotation = 0.0;
}

void Server::Minion::spell1(const GameData::CommandStruct::Fire &arg)
{
}

void Server::Minion::spell2(const GameData::CommandStruct::Shield arg)
{
}

void Server::Minion::update(float elapsedMilliseconds)
{
  if (_data.health <= 0)
    {
      _world.addUnitToDestroy(this);
      return;
    }
  
  this->move();
  // TODO: do this in a function, and improve precision
#define PI 3.14
  while (_body->GetAngle() > 2 * PI)
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() - 2 * PI);
  while (_body->GetAngle() < 0)
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() + 2 * PI);
  _body->SetAngularVelocity(rotation);
}

void Server::Minion::intraCollision(Object *o)
{
  if (o->getType() == Object::Element)
    this->intraCollisionElement(o);
  else if(o->getType() == Object::Bullet)
    this->intraCollisionBullet(o);
  else if(o->getType() == Object::Unit)
    this->intraCollisionUnit(o);
}

void Server::Minion::intraCollisionUnit(Object *o)
{
  std::cout<<"Unit:!:Collision with a unit and unit!"<<std::endl;
}

void Server::Minion::intraCollisionElement(Object *o)
{
  std::cout<<"Unit::Collision with a unit and element!"<<std::endl;
}

void Server::Minion::intraCollisionBullet(Object *o)
{
  _data.health -= 2;
  std::cout<<"Unit::Collision with a unit and bullet!"<<std::endl;
}
