//
// Bullet.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 17:37:09 2012 thierry berger
// Last update Fri Sep 14 11:05:29 2012 thierry berger
//

#ifndef SERVER_BULLET_HPP
# define SERVER_BULLET_HPP

#include "../GameData/Bullet.hpp"
#include "Object.hpp"

namespace Server
{
  class Bullet : public Object
  {
  public:
    GameData::Bullet _data;

    Bullet(World& w, int id, int damage) : Object(w, Object::Bullet, id), _data(damage, id) {}
    virtual b2Body*	setBody();
    
    /// TODO: implement these functions (or delete all serialized related stuff (nah..))
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
    virtual int	getClassId() const {return 0;}
  };
}

#endif
