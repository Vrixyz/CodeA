//
// Unit.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:00:00 2012 mathieu leurquin
// Last update Tue Mar  5 10:31:21 2013 mathieu leurquin
//

#ifndef SERVER_UNIT_HPP
# define SERVER_UNIT_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "Player.hpp"
#include "BitField.hpp"
#include <vector>
#include "IUnit.hpp"

namespace Server
{
  class World;
  class	Mage : public IUnit
  {
  public:
    //   GameData::Unit _data; // now in IUnit directly.
    b2Vec2 current;
    float rotation; // that's useless if we dont't have a cannon" : check body position.
    std::vector<float>spellTimer;

    Mage(World& world) : IUnit(world), current(0, 0), rotation(0) {
      // timer used for fire
      spellTimer.push_back(0);
      // timer used for shield
      spellTimer.push_back(0);
      this->_data.health = 5;
    }
    virtual ~Mage() {}

    virtual void addPlayer(Player* p);
    virtual bool belongsToPlayer(int idPlayer) const;

    virtual void setMove(const GameData::CommandStruct::Move&);
    virtual void setRotateLeft();
    virtual void setRotateRight();
    virtual void setRotateStop();
    virtual void spell1(const GameData::CommandStruct::Fire&);
    virtual void spell2(const GameData::CommandStruct::Shield arg);
    virtual void moveTo(int x, int y);

    virtual b2Body*	setBody(BitField *b);
    const GameData::Unit& getData() const {return _data;}
    virtual void update(float elapsedMilliseconds);
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>&) {return false;}
    virtual int	getClassId() const {return 0;}

  protected:
    void move();

    virtual void intraCollision(Object *o);
    virtual void intraCollisionUnit(Object *o);
    virtual void intraCollisionBullet(Object *o);
    virtual void intraCollisionElement(Object *o);
  };
}

#endif
