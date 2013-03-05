// World.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 14:49:21 2012 thierry berger
// Last update Wed Feb 27 10:15:50 2013 mathieu leurquin
//

#include "World.hpp"
#include <cmath>
#include <stdlib.h>
#include <time.h>

MyContactListener Server::World::myContactListenerInstance;

Server::World::~World()
{
  // TODO: we certainly have stuff to do there.
}


void	Server::World::init(int masterPort, char* masterIp, int width, int height)
{
  srand (time(NULL));
  // // FIXME: we must create the player and the unit at the connection !
  // BitField *b = new  BitField(Server::BitField::MAGE, Server::BitField::MAGE);
  


  BitField *obs = new BitField(Server::BitField::OBSTACLE, Server::BitField::TEAM1_UNIT | Server::BitField::TEAM2_UNIT 
			       | Server::BitField::TEAM1_BULLET | Server::BitField::TEAM2_BULLET | Server::BitField::PORTAL);
  
  // u = this->createUnit(b);
  // u->addPlayer(&this->createPlayer(0));

  //  this->createElement(true, 100, 100, obs, -1);
  
  // this->createElement(true, 1, 10, shield);
  
  // _physicWorld.SetContactListener(&World::myContactListenerInstance);
  
  communication.init();

  
  _commandManagerMaster = new CommandManager<World, int, int>(this);
  _commandManagerMaster->addCallback(MasterData::Command::PLAYER_JOIN, 
				     _commandManagerMaster->createCallback(&World::prepare_new_client));
  
  communication.setCommandManagerMaster(_commandManagerMaster);

  communication.connect(masterPort, masterIp);


  std::string				name;
  
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  
  name = "No name";
  packet.pack((int)MasterData::Command::CONNECT_SERVER);
  MasterData::CoServer serv(_port, name);
  packet.pack(serv);
  communication.sendToMaster(sbuf);


  _commandManager = new CommandManager<World, int, int>(this);
  // TODO: commandManager a factory !
  _commandManager->addCallback(GameData::Command::Fire,
			       _commandManager->createCallback(&World::fire));
  _commandManager->addCallback(GameData::Command::AimTo,
			       _commandManager->createCallback(&World::aimTo));
  _commandManager->addCallback(GameData::Command::MoveTo,
			       _commandManager->createCallback(&World::moveTo));
  _commandManager->addCallback(GameData::Command::Move,
			       _commandManager->createCallback(&World::askMove));
  _commandManager->addCallback(GameData::Command::RotateLeft,
			       _commandManager->createCallback(&World::rotateLeft));
  _commandManager->addCallback(GameData::Command::RotateRight,
			       _commandManager->createCallback(&World::rotateRight));
  _commandManager->addCallback(GameData::Command::RotateStop,
			       _commandManager->createCallback(&World::rotateStop));
  _commandManager->addCallback(GameData::Command::Shield,
			       _commandManager->createCallback(&World::shield));
  _commandManager->addCallback(GameData::Command::BePlayer,
			       _commandManager->createCallback(&World::addPlayer));
  communication.setCommandManager(_commandManager);
}

void	Server::World::run()
{
  b2Timer timer;
  float32 rest = 0;

  timer.Reset();
  /// FIXME: ugly infinite loop
  while (1)
    {
      if (timer.GetMilliseconds() + rest >= TIMESTEP)
	{
	  rest = timer.GetMilliseconds() + rest - TIMESTEP;
	  timer.Reset();
	  _physicWorld.Step(TIMESTEP, VELOCITY_ITERATION, POSITION_ITERATION);
 	    
	  communication._command->interpretCommands();
	  communication._master_cmd->interpretCommands();
	  // std::cout << "end interpret cmd master :" << std::endl;
	  for (std::list<Server::IUnit*>::iterator itu = units.begin(); itu != units.end(); itu++)
	    {
	      (*itu)->update(TIMESTEP);
	    }

	  sendUpdatesToClients();
	  
	  
	  communication.cleanClients();
	  // TODO: delete client on Communication and add a handler
	  //  // deleting clients:
	  // boost::lock_guard<boost::mutex> lock(communication._m_clients);	  
	  //  for (std::list<int>::iterator it = communication.clientsErase.begin(); it != communication.clientsErase.end(); it++)
	  //    {
	  //      std::cout << "erasing client " << *it << std::endl;
	  //      communication.clients.erase(*it);
	  //    }
	  destroyUnit();
	  destroyBullet();
	  destroyElement();
	}
      // FIXME: think more about that sleep.
      usleep(500);
    }  
}

Server::Player&	Server::World::createPlayer(int id)
{
  Player* p = new Player(id);

  players.push_back(p);
  return *p;
}

Server::Mage* Server::World::createMage(BitField *b, Player* p)
{
  Server::Mage* u = new Server::Mage(*this);
  u->setBody(b);
  if (p != NULL)
    u->addPlayer(p);
  units.push_back(u);
  return u;
}

Server::Minion *Server::World::createMinion(BitField *b, Player* p, float x, float y)
{
  Minion* m = new Server::Minion(*this);
  m->setBody(b, x, y);
  if (p != NULL)
    m->addPlayer(p);
  units.push_back(m);
  return m;
}

Server::Portal* Server::World::createPortal(BitField *b, Player* player)
{
  Server::Portal* p = new Server::Portal(*this);
  
  p->setBody(b, rand() % 500 - 250, rand() % 500 - 250);
  if (p != NULL)
    p->addPlayer(player);
  units.push_back(p);
  return p;
} 

Server::Element* Server::World::createElement(bool walkable, float width, float height, BitField *b, int idU)
{
  Server::Element* e = new Element(*this, walkable);
  e->setBody(b, width, height);
  elements.push_back(e);  
  return e;
}

Server::Bullet*  Server::World::createBullet(int damage, float angle, b2Vec2 pos, int idUnit, BitField *bit)
{
  Server::Bullet* b = new Bullet(*this, damage);

  b->setBody(angle, pos, bit);
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

Server::IUnit* Server::World::getUnit(int id)
{
  for (std::list<IUnit*>::iterator it = units.begin(); it != units.end(); it++)
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

void Server::World::addUnitToDestroy(Server::IUnit *u)
{
  for (std::list<IUnit*>::iterator it = units.begin(); it != units.end(); it++)
    {
      if ((*it) == u)
	{
	  std::cout<<"T MORT"<<std::endl;
	  unitsErase.insert(*it);
	}
    }
}

void Server::World::addElemToDestroy(Server::Element *u)
{
  for (std::list<Element*>::iterator it = elements.begin(); it != elements.end(); it++)
    {
      if ((*it) == u)
	{
	  std::cout<<"T MORT"<<std::endl;
	  elementsErase.insert(*it);
	}
    }
}

void Server::World::addBulletToDestroy(Server::Bullet *u)
{
  for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      if ((*it) == u)
	{
	  std::cout<<"T MORT"<<std::endl;
	  bulletsErase.insert(*it);
	}
    }
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

// TODO: iterate on players, rather than clients, and instaure command queuing for communication Server->Communication
void	Server::World::sendUpdatesToClients()
{
  boost::lock_guard<boost::mutex> lock(communication._m_clients);
  for (std::map<int, tcp_connection::pointer>::const_iterator
	 it = communication.clients.begin(); it != communication.clients.end();
       it++)
    {
      msgpack::sbuffer sbuf;
      msgpack::packer<msgpack::sbuffer> packet(&sbuf);
	       

      packet.pack((int)GameData::InformationId::EntireWorld);
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
}
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
      // packet.pack(getPhysics((*it)->getBody()));
    }
  /// Packing units
  for (std::list<IUnit*>::const_iterator it = units.begin(); it != units.end(); it++)
    {
      toPack = static_cast<Serializable const*>(((*it)->getBody())->GetUserData());
      toPack->serialize(packet);
    }
  /// Packing bullets
  for (std::list<Bullet*>::const_iterator it = bullets.begin(); it != bullets.end(); it++)
    {
      toPack = static_cast<Serializable const*>(((*it)->getBody())->GetUserData());
      toPack->serialize(packet);
      // packet.pack(getPhysics((*it)->getBody()));
    }
}

bool Server::World::unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}

int	Server::World::getClassId() const {return 0;}


void Server::World::destroyUnit()
{
  std::set<IUnit*>::iterator it = unitsErase.begin();
  std::set<IUnit*>::iterator end = unitsErase.end();
  for (; it!=end; ++it) {
    IUnit* dyingUnit = *it;
    
    //  delete dyingUnit;
    // ... and remove it from main list of balls
    std::list<IUnit*>::iterator it = std::find(units.begin(), units.end(), dyingUnit);
    if (it != units.end())
      units.erase(it);
    unitsErase.erase(*it);
  } 

  //unitsErase.clear();
}

void Server::World::destroyBullet()
{  
  std::set<Bullet*>::iterator it = bulletsErase.begin();
  std::set<Bullet*>::iterator end = bulletsErase.end();
  for (; it!=end; ++it) {
    Bullet* dyingBullet = *it;
    
    //delete dyingBullet;
    
    //... and remove it from main list of balls
    std::list<Bullet*>::iterator it = std::find(bullets.begin(), bullets.end(), dyingBullet);
    if (it != bullets.end())
      bullets.erase(it);
    bulletsErase.erase(*it);
  } 
  //bulletsErase.clear();
}

void Server::World::destroyElement()
{
  std::set<Element*>::iterator it = elementsErase.begin();
  std::set<Element*>::iterator end = elementsErase.end();
  for (; it!=end; ++it) {
    Element* dyingElement = *it;
    std::cout << "destroying element" << std::endl;
  
  
    //... and remove it from main list of balls
    std::list<Element*>::iterator it = std::find(elements.begin(), elements.end(), dyingElement);
    if (it != elements.end())
      elements.erase(it);
    elementsErase.erase(*it);
    //    delete dyingElement; // NOTE: deleted by erase();
  } 
  //elementsErase.clear();
}


// GameData::Physics Server::World::getPhysics(const b2Body* body) const
// {
//   GameData::Physics physics;
//   b2Vec2 position = body->GetPosition();
//   physics.x = position.x;
//   physics.y = position.y;
//   physics.angle = body->GetAngle();

//   /// assuming that shapes are only simple rectangles (real simple, centered at 0)
//   const b2PolygonShape* shape = static_cast<const b2PolygonShape*>(body->GetFixtureList()->GetShape());
//   for (int i = 0; i < shape->GetVertexCount(); ++i)
//     {
//       b2Vec2 vertice = shape->GetVertex(i);

//       physics.vertices.push_back(GameData::Physics::Coord(vertice.x, vertice.y));
//     }
//   return physics;
// }

void Server::World::fire(int idClient, GameData::CommandStruct::Fire arg)
{
  IUnit* u = getUnit(arg.idUnit);
  
  if (u == NULL || u->belongsToPlayer(idClient) == false)
    return;
  u->spell1(arg);
}

void Server::World::aimTo(int idClient, GameData::CommandStruct::Aim)
{
}

void Server::World::moveTo(int idClient, GameData::CommandStruct::Move)
{
}

void Server::World::rotateLeft(int idClient, GameData::CommandStruct::Rotate arg)
{
  IUnit* u = getUnit(arg.idUnit);

  if (u == NULL || u->belongsToPlayer(idClient) == false)
    return;
  u->setRotateLeft();
}

void Server::World::rotateRight(int idClient, GameData::CommandStruct::Rotate arg)
{
  IUnit* u = getUnit(arg.idUnit);

  if (u == NULL || u->belongsToPlayer(idClient) == false)
    return;
  u->setRotateRight();
}

void Server::World::rotateStop(int idClient, GameData::CommandStruct::Rotate arg)
{
  IUnit* u = getUnit(arg.idUnit);
  
  if (u == NULL || u->belongsToPlayer(idClient) == false)
    return;
  u->setRotateStop();
}

void Server::World::shield(int idClient, GameData::CommandStruct::Shield arg)
{
  IUnit* u = getUnit(arg.idUnit);

  if (u == NULL || u->belongsToPlayer(idClient) == false)
      return;
  std::cout<<"shield"<<std::endl;
  u->spell2(arg);
}

void Server::World::askMove(int idClient, GameData::CommandStruct::Move arg)
{
  IUnit* u = getUnit(arg.idUnit);

  if (u == NULL || u->belongsToPlayer(idClient) == false)
    return;
  u->setMove(arg);
}

void	Server::World::addPlayer(int idClient)
{
  std::list<Player*>::const_iterator it;
  // TODO: check if there's room for a new player
  for (it = players.begin(); it != players.end(); it++)
    {
      if ((*it)->id == idClient)
	return ; // TODO: send to client that he is already a player.
    }

  //FOR MAGE VS MAGE TEST
  Player p = createPlayer(idClient);
 
  BitField *b;
  if (players.size() == 1)
    {
      b = new  BitField(Server::BitField::TEAM1_UNIT, Server::BitField::TEAM2_BULLET | Server::BitField::TEAM2_UNIT | Server::BitField::OBSTACLE | Server::BitField::PORTAL);
      createMage(b, &(p));
      std::cout<<"team1"<<std::endl;      
    }
  else
    {
      BitField *bp = new  BitField(Server::BitField::PORTAL, Server::BitField::TEAM2_BULLET | Server::BitField::TEAM2_UNIT | Server::BitField::TEAM1_BULLET | Server::BitField::TEAM1_UNIT | Server::BitField::OBSTACLE | Server::BitField::PORTAL);
      createPortal(bp, &(p));
      createPortal(bp, &(p));
      createPortal(bp, &(p));
    }

  
  // TODO: we might want to wait all players before creating the units
     //createPortal(b, &(createPlayer(idClient)));
  // createMage(b, &(p));
  // FIXME: use a fucking QueueSendToServer !
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  /// TODO: sepcify type of sent data (here: World)
  packet.pack((int)GameData::InformationId::PlayerDefinition);
  GameData::Information::PlayerDefinition playerDefinition;

  playerDefinition.idPlayer = idClient;

  packet.pack(playerDefinition);
	       
  communication.sendToClient(sbuf, idClient);
}

void Server::World::prepare_new_client(int, MasterData::InfosPlayer data)
{
  std::cout << "player " << data.name << " wants to connect from ip : " << data.ip << std::endl;
}
