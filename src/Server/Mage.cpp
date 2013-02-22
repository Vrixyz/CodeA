//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Fri Feb 22 12:45:08 2013 mathieu leurquin
//

#include "World.hpp"
#include "Mage.hpp"

b2Body*	Server::Mage::setBody(BitField *b)
{
  b2BodyDef uBDef;

  uBDef.type = b2_dynamicBody;
  uBDef.userData = this;
  uBDef.fixedRotation = true;
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

void	Server::Mage::addPlayer(Player* p)
{
  _data.playersId.push_back(p->id);
}

bool	Server::Mage::belongsToPlayer(int idPlayer) const
{
   for (std::list<uint32_t>::const_iterator it = _data.playersId.begin(); it != _data.playersId.end(); it++)
    {
      if ((*it) == idPlayer)
	return true;
      return false;
    }
   return false;
}

void	Server::Mage::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
  packet.pack(this->getPhysics());
}

void Server::Mage::move()
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

void Server::Mage::setMove(const GameData::CommandStruct::Move& arg)
{
  current.x = arg.x;
  current.y = arg.y;
}

void Server::Mage::setRotateLeft()
{
  rotation = -0.001;
}

void Server::Mage::setRotateRight()
{
  rotation = 0.001;
}

void Server::Mage::setRotateStop()
{
  rotation = 0.0;
}

void Server::Mage::spell1(const GameData::CommandStruct::Fire &arg)
{
  std::vector<float>::iterator fire = spellTimer.begin();
  if ((*fire) != 0)
    return;

  //check friendly or not
  BitField *bullet;
  if (this->id == 0)
    {
      bullet = new BitField(Server::BitField::TEAM1_BULLET, Server::BitField::TEAM2_UNIT | Server::BitField::OBSTACLE | Server::BitField::TEAM2_SHIELD | Server::BitField::PORTAL);
      std::cout<<"team 1"<<std::endl;
    }
  else
    {
      bullet = new BitField(Server::BitField::TEAM2_BULLET, Server::BitField::TEAM1_UNIT | Server::BitField::OBSTACLE | Server::BitField::PORTAL);
      std::cout<<"team 2"<<std::endl;
    }
  Server::Bullet *b = _world.createBullet(10, this->getBody()->GetAngle(), this->getBody()->GetPosition(), arg.idUnit, bullet);
  float angle;

  angle = this->getBody()->GetAngle() * 57.2957795;
  angle = (int)angle % (int)360;
  angle = angle  < 0 ? -angle : angle;
  if (angle >= 0 && angle < 90)
    b->getBody()->ApplyLinearImpulse(b2Vec2(1, 1 / (tan(b->getBody()->GetAngle()))), b->getBody()->GetWorldCenter());
  else if (angle >= 90 && angle < 180)
    b->getBody()->ApplyLinearImpulse(b2Vec2(1, (-1) * tan(b->getBody()->GetAngle() - 1.5707963267949)), b->getBody()->GetWorldCenter());
  else if (angle >= 180 && angle < 270)
    b->getBody()->ApplyLinearImpulse(b2Vec2(-1, -1 / (tan(b->getBody()->GetAngle() - 3.1415926535898))), b->getBody()->GetWorldCenter());
  else
    b->getBody()->ApplyLinearImpulse(b2Vec2(-1, (tan(b->getBody()->GetAngle() - 4.7123889803847))), b->getBody()->GetWorldCenter());
  (*fire) = -1;
}

void Server::Mage::spell2(const GameData::CommandStruct::Shield arg)
{
  std::vector<float>::iterator sh = this->spellTimer.end();
  std::cout<<*sh<<std::endl;
  // if ((*sh) != 0)
  //   return;
  //check friendly or not
  BitField *shield;
  if (this->id == 0)
    shield = new BitField(Server::BitField::TEAM1_SHIELD, Server::BitField::OBSTACLE | Server::BitField::TEAM2_BULLET);
  else
    shield = new BitField(Server::BitField::TEAM2_SHIELD, Server::BitField::OBSTACLE | Server::BitField::TEAM1_BULLET);
  
  b2Vec2 position = this->getBody()->GetPosition();
  
  Server::Element *e = _world.createElement(true, (float)10, (float)1, shield, this->id);
    // Server::Element *e = new Server::Element(*this, (int)elements.size(), true, this->id);
  
  e->setBody(shield, 10 , 1,  position.x, position.y);
  e->getBody()->SetTransform(position, this->getBody()->GetAngle());
  _world.elements.push_back(e); 
  (*sh) = -1;
}

void Server::Mage::update(float elapsedMilliseconds)
{
  // b2Vec2 curVel = _body->GetLinearVelocity();
  // if (curVel.x != current.x && curVel.y != current.y)
  if (_data.health <= 0)
    {
      _world.addPlayerToDestroy(this);
      return;
    }

  this->move();
  std::vector<float>::iterator fire = this->spellTimer.begin();
  std::vector<float>::iterator shield = this->spellTimer.end();

   //update timer
  
  if ((*fire) > 0)
    (*fire) += elapsedMilliseconds;
  if ((*shield) > 0)
    (*shield) += elapsedMilliseconds;
 
  
  //shield, fire active ?
  
  if ((*fire) == -1)
    (*fire) += 1 + elapsedMilliseconds;
  if ((*shield) != -1)
    (*shield) += 1 + elapsedMilliseconds;
  
  //shiled, fire finish ?

  if ((*fire) > 3000)
    {
      _world.bulletsErase.insert(_world.getBullet(this->id));
      (*fire) = 0;
    }
  if ((*shield) > 5000)
    {
      _world.elementsErase.insert(_world.getElement(this->id));
      (*shield) = 0;
    }
  

  // TODO: do this in a function, and improve precision
#define PI 3.14
  while (_body->GetAngle() > 2 * PI)
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() - 2 * PI);
  while (_body->GetAngle() < 0)
    _body->SetTransform(_body->GetPosition(), _body->GetAngle() + 2 * PI);
  _body->SetAngularVelocity(rotation);
}

void Server::Mage::intraCollision(Object *o)
{
  if (o->getType() == Object::Element)
    this->intraCollisionElement(o);
  else if(o->getType() == Object::Bullet)
    this->intraCollisionBullet(o);
  else if(o->getType() == Object::Unit)
    this->intraCollisionUnit(o);
}

void Server::Mage::intraCollisionUnit(Object *o)
{
  _data.health -= 1;
  std::cout<<"Unit:!:Collision with a unit and unit!"<<std::endl;
}

void Server::Mage::intraCollisionElement(Object *o)
{
  std::cout<<"Unit::Collision with a unit and element!"<<std::endl;
}

void Server::Mage::intraCollisionBullet(Object *o)
{
  _data.health -= 2;
  std::cout<<"Unit::Collision with a unit and bullet!"<<std::endl;
}
