//
// Bullet.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Fri Sep 14 10:40:12 2012 thierry berger
// Last update Sat Mar  2 13:20:10 2013 mathieu leurquin
//

#include "World.hpp"
#include "Bullet.hpp"

static unsigned int _incr_id = 0;

Server::Bullet::Bullet(World& w, int damage, int idU) : Object(w, Object::Bullet, _incr_id), _data(damage, _incr_id)
{
  _idU = idU;
  _incr_id++;
}


b2Body*	Server::Bullet::setBody(float angle, b2Vec2 position, BitField *b)
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

  fDef.filter.categoryBits = b->what;
  fDef.filter.maskBits = b->collide;


  this->_body->CreateFixture(&fDef);
  return this->_body;
}

void	Server::Bullet::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
  packet.pack(this->getPhysics());
}

Server::Bullet::~Bullet()
{
  _body->GetWorld()->DestroyBody(_body);
}

void Server::Bullet::intraCollision(Object *o)
{
  _world.addBulletToDestroy(this);
  if (o->getType() == Object::Element)
    this->intraCollisionElement(o);
  else if(o->getType() == Object::Bullet)
    this->intraCollisionBullet(o);
  else if(o->getType() == Object::Unit)
    this->intraCollisionUnit(o);
}

void Server::Bullet::intraCollisionUnit(Object *)
{
  std::cout<<"Bullet::Collision with a bullet and unit!"<<std::endl;
}

void Server::Bullet::intraCollisionElement(Object *)
{
  std::cout<<"Bullet::Collision with a bullet and elemnt!"<<std::endl;
}

void Server::Bullet::intraCollisionBullet(Object *)
{
  std::cout<<"Bullet::Collision with a bullet and bullet!"<<std::endl;
}
