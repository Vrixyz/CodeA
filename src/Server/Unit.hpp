//
// Unit.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:00:00 2012 mathieu leurquin
// Last update Thu Sep 13 15:54:07 2012 thierry berger
//

#ifndef SERVER_UNIT_HPP
# define SERVER_UNIT_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "Object.hpp"
#include "Player.hpp"

namespace Server
{
  class	Unit : public Object
  {
  public:
    GameData::Unit _data;

    Unit(World& world, int id) : Object(world, Object::Unit, id), _data(id, 10) {}

    const GameData::Unit& getData() const {return _data;}
    void addPlayer(Player* p);
    void fire(float x, float y);
    void aimTo(float x, float y);
    void moveTo(float x, float y);
    void startMoving();
    void stopMoving();
    void goUp();
    void goRight();
    void goDown();
    void goLeft();
    void stopUp();
    void stopRight();
    void stopDown();
    void stopLeft();

    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const {return;}
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
    virtual int	getClassId() const {return 0;}
  };
}

#endif
