//
// Unit.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:00:00 2012 mathieu leurquin
// Last update Sat Nov 17 10:33:49 2012 mathieu leurquin
//

#ifndef SERVER_UNIT_HPP
# define SERVER_UNIT_HPP

#include <msgpack.hpp>
#include "../GameData/Unit.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "BitField.hpp"
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
      spellTimer.push_back(0);
      spellTimer.push_back(0);
    }
    virtual b2Body*	setBody(BitField *b);
    const GameData::Unit& getData() const {return _data;}
    void addPlayer(Player* p);
    bool ownPlayer(int idPlayer);
    void move(int x, int y);
    void askMove(int idClient, int x, int y);
    void askRotateLeft(int idPlayer);
    void askRotateRight(int idPlayer);
    void askRotateStop(int idPlayer);

    virtual void update(float elapsedMilliseconds);
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
    virtual int	getClassId() const {return 0;}
    
  };
}

#endif
