//
// Portal.hpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Thu Feb 21 14:03:36 2013 mathieu leurquin
// Last update Wed Apr 10 10:54:31 2013 mathieu leurquin
//

#ifndef SERVER_PORTAL_HPP
# define SERVER_PORTAL_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "BitField.hpp"
#include <vector>
#include "IUnit.hpp"

namespace Server
{
  class World;
  class	Portal : public IUnit
  {
  public:
    //    GameData::Unit _data;
    b2Vec2 current;
    float pop;
    int team;
    Portal(World& world, int _team) : IUnit(world), current(0, 0){
      pop = 0;
      _data.health = 5;
      team = _team;
    }
    virtual ~Portal() {}

    virtual void addPlayer(Player* p);
    virtual bool belongsToPlayer(int idPlayer) const;

    virtual void setMove(const GameData::CommandStruct::Move&);
    virtual void setRotateLeft();
    virtual void setRotateRight();
    virtual void setRotateStop();
    virtual void spell1(const GameData::CommandStruct::Fire&);
    virtual void spell2(const GameData::CommandStruct::Shield arg);

    virtual void moveTo(int x, int y);
    virtual b2Body* setBody(BitField *b, float x, float y);
    const GameData::Unit& getData() const {return _data;}
    void createMinion();
    void update(float elapsedMilliseconds);
    void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    bool unSerialize(msgpack::packer<msgpack::sbuffer>&) {return false;}
    int	getClassId() const {return 0;}
  protected:
  
    virtual void intraCollision(Object *o);
    virtual void intraCollisionUnit(Object *o);
    virtual void intraCollisionBullet(Object *o);
    virtual void intraCollisionElement(Object *o);
  };
}

#endif
