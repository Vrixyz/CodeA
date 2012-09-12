//
// World.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 10:46:49 2012 thierry berger
// Last update Wed Sep 12 18:18:09 2012 thierry berger
//

#ifndef SERVER_WORLD_HPP
# define SERVER_WORLD_HPP

#include <Box2D/Box2D.h>
#include "../GameData/World.hpp"
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
    b2Body& getUnit(int id);
    b2Body& getElement(int id);

    virtual void* serialize(int& finalLength) const {return 0;};
    virtual int	getClassId() const {return 0;};
  private:
    b2World _physicWorld;
  };
}

#include "Player.hpp"

#endif
