//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Sat Jan  5 18:00:43 2013 mathieu leurquin
//

#ifndef SERVER_WORLD_HPP
# define SERVER_WORLD_HPP

#include <Box2D/Box2D.h>
#include <boost/asio/buffer.hpp>
#include "Communication.hpp"
#include <boost/asio.hpp>
#include "../GameData/World.hpp"
#include "../GameData/Physics.hpp"
#include "../GameData/Unit.hpp"
#include "../GameData/Command.hpp"
#include "../GameData/Information.hpp"
#include "../GameData/Serializable.hpp"
#include "myContactListener.hpp"
#include "Element.hpp"
#include "Bullet.hpp"
#include "Unit.hpp"
#include "BitField.hpp"
#include <list>
#include <set>
#define VELOCITY_ITERATION 6
#define POSITION_ITERATION 2
#define TIMESTEP 16.666666666667

namespace Server
{
  class Player;
  class Unit;
  class Element;
  class Bullet;
  // class MyContactListener;
  class	World : GameData::Serializable
  {
  public:
    // static MyContactListener myContactListenerInstance;
    /// TODO: Add a trash list to remove safely the bodies
    Communication<World>       communication;
    std::list<Server::Element*>	elements;
    std::list<Server::Unit*> units;
    std::list<Server::Bullet*>	bullets;
    std::set<Server::Element*>	elementsErase;
    std::set<Server::Unit*> unitsErase;
    std::set<Server::Bullet*>	bulletsErase;
    std::list<Player*>	players;
    b2World _physicWorld;
    static MyContactListener myContactListenerInstance;

    World() : _physicWorld(b2Vec2(0, 0)) {
      _physicWorld.SetContactListener(&myContactListenerInstance);
    }
    ~World();
    void init(int width, int height);
    void run();
    void handleContact(b2Body object1, b2Body object2);
    Player& createPlayer(int id);
    Server::Unit* createUnit(BitField *b, Player* p = NULL);
    Server::Element* createElement(bool walkable, float width, float height, BitField *b, int idUnit);
    Server::Bullet* createBullet(int damage, float angle, b2Vec2 position, int idUnit, BitField *b);
    Player* getPlayer(int id);
    Server::Unit* getUnit(int id);
    Server::Element* getElement(int id);
    Server::Bullet* getBullet(int id);
    void destroyPlayer(int);
    void destroyUnit();
    void destroyElement();
    void destroyBullet();
    
    //fct handling command
    void fire(int idClient, GameData::CommandStruct::Fire);
    void aimTo(int idClient, GameData::CommandStruct::Aim);
    void moveTo(int idClient, GameData::CommandStruct::Move);
    void rotateLeft(int idClient, GameData::CommandStruct::Rotate);
    void rotateRight(int idClient, GameData::CommandStruct::Rotate);
    void rotateStop(int idClient, GameData::CommandStruct::Rotate);
    void shield(int idClient, GameData::CommandStruct::Shield);
    void askMove(int idClient, GameData::CommandStruct::Move cmd);
    void addPlayer(int idClient);

    void sendUpdatesToClients();
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet);
    virtual int	getClassId() const;

  private:
    CommandManager<World, int, int>* _commandManager;
    GameData::Physics getPhysics(const b2Body* body) const;
  };
}

#include "Player.hpp"
// #include "myContactListener.hpp"

#endif
