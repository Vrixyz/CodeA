//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Thu Sep 13 15:39:02 2012 thierry berger
//

#ifndef SERVER_WORLD_HPP
# define SERVER_WORLD_HPP

#include <Box2D/Box2D.h>
#include "../GameData/World.hpp"
#include "../GameData/Physics.hpp"
#include "../GameData/Unit.hpp"
#include "../GameData/Serializable.hpp"
#include "Element.hpp"
#include "Bullet.hpp"
#include "Unit.hpp"

#include <list>

namespace Server
{
  class Player;

  class	World : GameData::Serializable
  {
  public:

    /// TODO: Add a trash list to remove safely the bodies
    std::list<b2Body*>	elements;
    std::list<b2Body*>	units;
    std::list<b2Body*>	bullets;
    std::list<Player*>	players;

    World() : _physicWorld(b2Vec2(0, 0)) {}
    void init();
    void run();
    void handleContact(b2Body object1, b2Body object2);
    Player& createPlayer(int id);
    b2Body& createUnit();
    b2Body& createElement(bool walkable, int width, int height);
    b2Body& createBullet(int damage);
    Player* getPlayer(int id);
    b2Body* getUnit(int id);
    b2Body* getElement(int id);
    b2Body* getBullet(int id);
    void destroyPlayer(int id);
    void destroyUnit(int id);
    void destroyElement(int id);
    void destroyBullet(int id);

    virtual void	serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet);
    virtual int	getClassId() const;

  private:
    b2World _physicWorld;

    b2Body* getFromList(std::list<b2Body*>, int id);
    void destroyFromList(std::list<b2Body*>, int id);
    GameData::Physics getPhysics(const b2Body* body) const;
  };
}

#include "Player.hpp"

#endif
