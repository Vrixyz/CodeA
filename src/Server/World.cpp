//
// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Tue Sep 18 15:54:11 2012 thierry berger
//

#include "World.hpp"

void	Server::World::init()
{
  static_cast<Unit*>(this->createUnit().GetUserData())->addPlayer(&this->createPlayer(4));
  this->createElement(true, 100, 100);
  communication.init();
}

void	Server::World::run()
{
  /// FIXME: ugly infinite loop
  b2Timer timer;
  float32 rest = 0;

  timer.Reset();
  while (1)
    {
      if (timer.GetMilliseconds() + rest >= TIMESTEP)
	{
	  rest = timer.GetMilliseconds() + rest - TIMESTEP;
	  timer.Reset();
	  _physicWorld.Step(TIMESTEP, VELOCITY_ITERATION, POSITION_ITERATION);



	  // DEBUG [

	  for (std::map<int, tcp_connection::pointer>::iterator
		 it = communication.clients.begin(); it != communication.clients.end();
	       it++)
	    {
	      msgpack::sbuffer sbuf;
	      msgpack::packer<msgpack::sbuffer> packet(&sbuf);

	      serialize(packet);
	      communication.sendToClient(sbuf, it->first);
	      // int newClient;


	      // communication.tryAccept(&newClient);

	      // communication.sendToClient(sbuf, newClient);
	      // std::cout << newClient << std::endl;
	      msgpack::unpacker pac;
 
	      //	  feeds the buffer.
	      pac.reserve_buffer(sbuf.size());
	  
	      memcpy(pac.buffer(), sbuf.data(), sbuf.size());
	      pac.buffer_consumed(sbuf.size());
 
	      //	  now starts streaming deserialization.
	      msgpack::unpacked result;
	      while(pac.next(&result)) {
		std::cout << result.get() << std::endl;
	      }

	    }

	  // ] DEBUG

	}
      // FIXME: think more about that sleep.
      usleep(500);
    }  
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
  b2Body* physicBody = u->setBody();

  units.push_back(physicBody);
  return *physicBody;
}

b2Body& Server::World::createElement(bool walkable, float width, float height)
{
  Element* e = new Element(*this, (int)elements.size(), walkable);
  b2Body* physicBody = e->setBody(width, height);

  elements.push_back(physicBody);  
  return *physicBody;
}

b2Body&  Server::World::createBullet(int damage)
{
  Bullet* b = new Bullet(*this, (int)elements.size(), damage);
  b2Body* physicBody = b->setBody();

  bullets.push_back(physicBody);
  return *physicBody;
}

Server::Player* Server::World::getPlayer(int id)
{
  for (std::list<Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
      if ((*it)->id == id)
	return *it;
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
  /// Packing GameData::World
  packet.pack((int)units.size());
  packet.pack((int)elements.size());
  packet.pack((int)bullets.size());
  Serializable const * toPack;
  /// Packing elements
  for (std::list<b2Body*>::const_iterator it = elements.begin(); it != elements.end(); it++)
    {
      toPack = static_cast<Serializable const*>((*it)->GetUserData());
      toPack->serialize(packet);
      packet.pack(getPhysics(*it));
    }
  /// Packing units
  for (std::list<b2Body*>::const_iterator it = units.begin(); it != units.end(); it++)
    {
      toPack = static_cast<Serializable const*>((*it)->GetUserData());
      toPack->serialize(packet);
      packet.pack(getPhysics(*it));
    }
  /// Packing bullets
  for (std::list<b2Body*>::const_iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      toPack = static_cast<Serializable const*>((*it)->GetUserData());
      toPack->serialize(packet);
      packet.pack(getPhysics(*it));
    }
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
  for (int i = 0; i < shape->GetVertexCount(); ++i)
    {
      b2Vec2 vertice = shape->GetVertex(i);

      physics.vertices.push_back(GameData::Physics::Coord(vertice.x, vertice.y));
    }
  return physics;
}
