//
// Unit.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:00:00 2012 mathieu leurquin
// Last update Thu Jan  3 13:21:04 2013 mathieu leurquin
//

#ifndef SERVER_UNIT_HPP
# define SERVER_UNIT_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "BitField.hpp"
#include "Bullet.hpp"
#include <vector>

namespace Server
{
  class	Unit : public Object
  {
  public:
    GameData::Unit _data;
    b2Vec2 current;
    float rotation;
    std::vector<float>spellTimer;

    Unit(World& world, int id) : Object(world, Object::Unit, id), _data(id, 10), current(0, 0), rotation(0) {
      // timer used for fire
      spellTimer.push_back(0);
      // timer used for shield
      spellTimer.push_back(0);
    }

    void addPlayer(Player* p);
    bool belongsToPlayer(int idPlayer) const;

    void setMove(const GameData::CommandStruct::Move&);
    void setRotateLeft();
    void setRotateRight();
    void setRotateStop();
    void setFire(const GameData::CommandStruct::Fire&);
    // TODO: setFire(...);


    virtual b2Body*	setBody(BitField *b);
    const GameData::Unit& getData() const {return _data;}
    virtual void update(float elapsedMilliseconds);
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
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
