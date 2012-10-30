//
// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Tue Oct 30 16:41:56 2012 mathieu leurquin
//

#include "World.hpp"

void	Server::World::init(int width, int height)
{
  fcts[GameData::Command::Fire] = &Server::Unit::fire;
  fcts[GameData::Command::MoveTo] = &Server::Unit::moveTo;
  fcts[GameData::Command::AimTo] = &Server::Unit::aimTo;  
  fcts[GameData::Command::Move] = &Server::Unit::move;

  Server::Unit *u;
  u = this->createUnit();

  // FIXME: we must create the player and the unit at the connection !
  u->addPlayer(&this->createPlayer(0));
  units.push_back(u);
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
	  std::cout << "debutloop" << std::endl;
      if (timer.GetMilliseconds() + rest >= TIMESTEP)
	{
	  rest = timer.GetMilliseconds() + rest - TIMESTEP;
	  timer.Reset();
	  _physicWorld.Step(TIMESTEP, VELOCITY_ITERATION, POSITION_ITERATION);
	  std::cout << "debut update boucle" << std::endl;


	  // DEBUG [

	  // thread safe on communication.clients because of the const specifier (std::map is thread safe on read operations)

	  // FIXME: Actually, seems not, add shared_ptr please (meaning no one else will modify this connection (like closing it !)
	   // boost::lock_guard<boost::mutex> lock(communication._m_clients);
	   for (std::map<int, tcp_connection::pointer>::const_iterator
		 it = communication.clients.begin(); it != communication.clients.end();
 	       it++)
	     {
	       msgpack::sbuffer sbuf;
	       msgpack::packer<msgpack::sbuffer> packet(&sbuf);
	       
	      /// TODO: sepcify type of sent data (here: World)
	      serialize(packet);
	      
	      //Execute cmd
 	      GameData::Command *c;

	      // FIXME: cmds is modified by World and Communication, which are different threads, this could lead to problems, lock_guard needed (or smth equivalent)
	      // INFO: this would lead to 2 locks at the same time for the same running code, care to deadlocks ! (unique/defer_lock might be an option)
	      std::cout<<"debut cmd"<<std::endl;
	      for (unsigned int i = 0; i < communication.cmds.size(); i++)
		{
		  if (communication.cmds[i].second == it->second)
		    {
		      for (std::list<Server::Unit*>::iterator itu = units.begin(); itu != units.end(); itu++)
			{
			  if ((*itu)->ownPlayer(it->first))
			    {
			      c = &communication.cmds[i].first;
			      ((*itu)->*fcts[c->getType()])(c->x, c->y);
			      communication.cmds.pop_back();
			      break;
			    }
			}
		    }
		}
	      std::cout<<"fin cmd"<<std::endl;
	      
	      // FIXME: sendToClient will lock_guard on clients, meaning it will deadlock if we shared_lock earlier. (solution would be to upgrade the lock (in sendToClient, and set an upgradeable lock in before this loop))
	      if (communication.sendToClient(sbuf, it->first))
	      	{
		  
	      	  msgpack::unpacker pac;
	      	  pac.reserve_buffer(sbuf.size());
	      	  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
	      	  pac.buffer_consumed(sbuf.size());
		  
	      	  //	  now starts streaming deserialization.
	      	  msgpack::unpacked result;
	      	  while(pac.next(&result)) {
	      	    // std::cout << result.get() << std::endl;
	      	  }
		  
	      	}
	      	  // ] DEBUG
	     }
	   //delete clients

	   std::cout<<"begin erase"<<std::endl;
	   for (std::list<int>::iterator it = communication.clientsErase.begin(); it != communication.clientsErase.end(); it++)
	     {
	       std::cout<<"erase"<<std::endl;
	       communication.clients.erase(*it);
	     }
	   std::cout<<"end erase"<<std::endl;
	   // FIXME: downgrade mutex here (should be at the end of sendToClient actually)
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

Server::Unit* Server::World::createUnit()
{
  Server::Unit* u = new Server::Unit(*this, (int)units.size());
  u->setBody();
  units.push_back(u);
  return u;
}

Server::Element* Server::World::createElement(bool walkable, float width, float height)
{
  Server::Element* e = new Element(*this, (int)elements.size(), walkable);
  e->setBody(width, height);
  elements.push_back(e);  
  return e;
}

Server::Bullet*  Server::World::createBullet(int damage)
{
  Server::Bullet* b = new Bullet(*this, (int)elements.size(), damage);
  b->setBody();
  bullets.push_back(b);
  return b;
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

Server::Unit* Server::World::getUnit(int id)
{
  for (std::list<Unit*>::iterator it = units.begin(); it != units.end(); it++)
    {
      if ((*it)->id == id)
	return (*it);
    }
  return NULL;
}

Server::Element* Server::World::getElement(int id)
{
  for (std::list<Element*>::iterator it = elements.begin(); it != elements.end(); it++)
    {
      if ((*it)->id == id)
	return (*it);
    }
  return NULL;
}

Server::Bullet* Server::World::getBullet(int id)
{
  for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      if ((*it)->id == id)
	return (*it);
    }
  return NULL;
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

// void Server::World::destroyUnit(int id)
// {
//   return destroyFromList(b2units, id);
// }

// void Server::World::destroyBullet(int id)
// {
//   return destroyFromList(bullets, id);
// }

void	Server::World::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  /// Packing GameData::World
  GameData::World *woo = new GameData::World;

  woo->nbElement = (int)(elements.size());
  woo->nbUnit = (int)(units.size());
  woo->nbBullet = (int)(bullets.size());
  packet.pack(*woo);
  Serializable const * toPack;
  /// Packing elements
  for (std::list<Element*>::const_iterator it = elements.begin(); it != elements.end(); it++)
    {
      toPack = static_cast<Serializable const*>(((*it)->getBody())->GetUserData());
      toPack->serialize(packet);
      packet.pack(getPhysics((*it)->getBody()));
    }
  /// Packing units
  for (std::list<Unit*>::const_iterator it = units.begin(); it != units.end(); it++)
    {
      toPack = static_cast<Serializable const*>(((*it)->getBody())->GetUserData());
      toPack->serialize(packet);
    }
  /// Packing bullets
  for (std::list<Bullet*>::const_iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      toPack = static_cast<Serializable const*>(((*it)->getBody())->GetUserData());
      toPack->serialize(packet);
      packet.pack(getPhysics((*it)->getBody()));
    }
}

bool Server::World::unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}

int	Server::World::getClassId() const {return 0;}


void Server::World::destroyUnit(int id)
{
  for (std::list<Unit*>::iterator it = units.begin(); it != units.end(); it++)
    {
      if ((*it)->id == id)
	{
	  /// TODO: put that in a list to delete later (it may cause problem if deletion in timestep)
	  _physicWorld.DestroyBody((*it)->getBody());
	  units.erase(it);
	  return;
	}
      else
	it++;
    }
  return;
}

void Server::World::destroyBullet(int id)
{
  for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      if ((*it)->id == id)
	{
	  /// TODO: put that in a list to delete later (it may cause problem if deletion in timestep)
	  _physicWorld.DestroyBody((*it)->getBody());
	  bullets.erase(it);
	  return;
	}
      else
	it++;
    }
  return;
}

void Server::World::destroyElement(int id)
{
  for (std::list<Element*>::iterator it = elements.begin(); it != elements.end(); it++)
    {
      if ((*it)->id == id)
	{
	  /// TODO: put that in a list to delete later (it may cause problem if deletion in timestep)
	  _physicWorld.DestroyBody((*it)->getBody());
	  elements.erase(it);
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
