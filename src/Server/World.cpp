//
// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Fri Nov  9 13:31:33 2012 mathieu leurquin
//

#include "World.hpp"

// Server::MyContactListener Server::World::myContactListenerInstance;

void	Server::World::init(int width, int height)
{
  Server::Unit *u;
 
  // FIXME: we must create the player and the unit at the connection !
  BitField *b = new  BitField(Server::BitField::MAGE, Server::BitField::MAGE);
  
  BitField *obs = new BitField(Server::BitField::OBSTACLE, Server::BitField::MAGE);
  
  // BitField *shield = new BitField(Server::BitField::SHIELD_MAGE, Server::BitField::OBSTACLE);

  u = this->createUnit(b);
   u->addPlayer(&this->createPlayer(0));
  this->createElement(true, 100, 100, obs);
  // this->createElement(true, 1, 10, shield);
  
  // _physicWorld.SetContactListener(&World::myContactListenerInstance);
  
  communication.init(this);
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

	  // thread safe on communication.clients because of the const specifier (std::map is thread safe on read operations)

	  // FIXME: Actually, seems not, add shared_ptr please (meaning no one else will modify this connection (like closing it !)
	   // boost::lock_guard<boost::mutex> lock(communication._m_clients);
	  boost::lock_guard<boost::mutex> lock(communication._m_clients);
	   // for (std::map<int, tcp_connection::pointer>::const_iterator
	   // 	 it = communication.clients.begin(); it != communication.clients.end();
 	   //     it++)
	   //   {
	      
	      //Interpret cmd
 	     //  GameData::Command *c;

 	    
	  communication._command->interpretCommands();
	  
	  for (std::list<Server::Unit*>::iterator itu = units.begin(); itu != units.end(); itu++)
	    {
	      (*itu)->update(TIMESTEP);
	    }
	  
	  for (std::map<int, tcp_connection::pointer>::const_iterator
	  	  it = communication.clients.begin(); it != communication.clients.end();
	  	it++)
	     {
	       // for (unsigned int i = 0; i < communication.cmds.s ize(); i++)
	     // 	{
	     // 	  if (communication.cmds[i].second == it->second)
	     // 	    {
	     // 	      // TODO: seek directly asked unit (send unitId from client)
	     // 	      for (std::list<Server::Unit*>::iterator itu = units.begin(); itu != units.end(); itu++)
	     // 		{
	     // 		  if ((*itu)->ownPlayer(it->first))
	     // 		    {
	     // 		      c = &communication.cmds[i].first;
	     // 		      ((*itu)->*fcts[c->getType()])(c->x, c->y);
	     // 		      break;
	     // 		    }
	     // 		}
	     // 	    }
	     // 	}
	     //  while (communication.cmds.size() > 0)
	     // 	{
	     // 	  communication.cmds.pop_back();
	     // 	}
	     // }
	       msgpack::sbuffer sbuf;
	       msgpack::packer<msgpack::sbuffer> packet(&sbuf);
	       
	       /// TODO: sepcify type of sent data (here: World)
	       /// TODO: send different packet depending on client (fog of war, etc...)
	       serialize(packet);
	       
	       
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

	   for (std::list<int>::iterator it = communication.clientsErase.begin(); it != communication.clientsErase.end(); it++)
	     {
	       communication.clients.erase(*it);
	     }
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

Server::Unit* Server::World::createUnit(BitField *b)
{
  Server::Unit* u = new Server::Unit(*this, (int)units.size());
  u->setBody(b);
  units.push_back(u);
  return u;
}

Server::Element* Server::World::createElement(bool walkable, float width, float height, BitField *b)
{
  Server::Element* e = new Element(*this, (int)elements.size(), walkable);
  e->setBody(b, width, height);
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
  physics.angle = body->GetAngle();
  /// assuming that shapes are only simple rectangles (real simple, centered at 0)
  const b2PolygonShape* shape = static_cast<const b2PolygonShape*>(body->GetFixtureList()->GetShape());
  for (int i = 0; i < shape->GetVertexCount(); ++i)
    {
      b2Vec2 vertice = shape->GetVertex(i);

      physics.vertices.push_back(GameData::Physics::Coord(vertice.x, vertice.y));
    }
  return physics;
}

void Server::World::askMove(boost::array<char, 127>cmd)
{
  int x;
  int y;
  std::list<Unit*>::iterator it = units.begin();
  msgpack::object obj;
  msgpack::unpacked result;
  msgpack::unpacker pac;
  
  pac.reserve_buffer(3);
  memcpy(pac.buffer(), cmd.elems, 3);
  pac.buffer_consumed(3);
  
  pac.next(&result);
  if (pac.next(&result))
    {
      obj = result.get();
      obj.convert(&x);
      (*it)->current.x = x;
    }
  if (pac.next(&result))
    {
      obj = result.get();
      obj.convert(&y);
      (*it)->current.y = y;
    }
}

void Server::World::fire(boost::array<char, 127>cmd)
{
}

void Server::World::aimTo(boost::array<char, 127>cmd)
{
}

void Server::World::moveTo(boost::array<char, 127>cmd)
{
}

void Server::World::shield(boost::array<char, 127>cmd)
{
  // BitField *shield = new BitField(Server::BitField::SHIELD_MAGE, Server::BitField::OBSTACLE);
  // Server::Element *e = new Server::Element(this->_world, (int)this->_world.elements.size(), false);
  // b2Vec2 position = this->getBody()->GetPosition();
  
  // e->setBody(shield, 1, 10, position.x + 10, position.y + 1);
  // _world.elements.push_back(e); 
}

void Server::World::rotateLeft(boost::array<char, 127>cmd)
{
  std::list<Unit*>::iterator it = units.begin();
  float impulse = (*it)->getBody()->GetInertia() * (100);// disregard time factor
  
  (*it)->getBody()->ApplyAngularImpulse(impulse);
}

void Server::World::rotateRight(boost::array<char, 127>cmd)
{
    std::cout<<"DROITEEEEEEEEEEEEEee"<<std::endl;
  std::list<Unit*>::iterator it = units.begin();
  std::cout<<(*it)->getBody()->GetInertia()<<std::endl;
  float impulse = (*it)->getBody()->GetInertia() * (100);// disregard time factor
 
  (*it)->getBody()->ApplyAngularImpulse(impulse);
}
 
void Server::World::rotateStop(boost::array<char, 127>cmd)
{
  float impulse = 0;
  std::list<Unit*>::iterator it = units.begin();

  (*it)->getBody()->ApplyAngularImpulse(impulse);
}
