//
// Minion.hpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Fri Feb 22 10:39:04 2013 mathieu leurquin
// Last update Wed Mar 27 11:17:13 2013 mathieu leurquin
//

#ifndef SERVER_MINION_HPP
# define SERVER_MINION_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "Player.hpp"
#include "BitField.hpp"
#include <vector>
#include "IUnit.hpp"

namespace Server
{
  class World;
  class	Minion : public IUnit
  {
  public:
    //    GameData::Unit _data; // now in IUnit directly
    b2Vec2 current;
    float rotation;
    int team;
    Minion(World& world, int _team) : IUnit(world), current(0, 0), rotation(0){
      _data.health = 1;
      team = _team;
    }
    virtual ~Minion() {}

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
