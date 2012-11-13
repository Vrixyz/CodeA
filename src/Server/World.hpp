//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Fri Nov  9 11:26:19 2012 mathieu leurquin
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
#include "../GameData/Serializable.hpp"
#include "Element.hpp"
#include "Bullet.hpp"
#include "Unit.hpp"
#include "BitField.hpp"
#include <list>

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
    std::list<Player*>	players;
    b2World _physicWorld;

    World() : _physicWorld(b2Vec2(0, 0)) {}
    ~World();
    void init(int width, int height);
    void run();
    void handleContact(b2Body object1, b2Body object2);
    Player& createPlayer(int id);
    Server::Unit* createUnit(BitField *b);
    Server::Element* createElement(bool walkable, float width, float height, BitField *b);
    Server::Bullet* createBullet(int damage);
    Player* getPlayer(int id);
    Server::Unit* getUnit(int id);
    Server::Element* getElement(int id);
    Server::Bullet* getBullet(int id);
    void destroyPlayer(int id);
    void destroyUnit(int id);
    void destroyElement(int id);
    void destroyBullet(int id);
    
    //fct handling command
    void fire(char* cmd);
    void aimTo(char* cmd);
    void moveTo(char* cmd);
    void rotateLeft(char* cmd);
    void rotateRight(char* cmd);
    void rotateStop(char* cmd);
    void shield(char* cmd);
    void askMove(char* cmd);
    void move(char* cmd);

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
