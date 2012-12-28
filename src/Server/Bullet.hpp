//
// Bullet.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 17:37:09 2012 thierry berger
// Last update Wed Dec 12 12:28:21 2012 mathieu leurquin
//

#ifndef SERVER_BULLET_HPP
# define SERVER_BULLET_HPP

#include "../GameData/Bullet.hpp"
#include "Object.hpp"
#include "BitField.hpp"
namespace Server
{
  class Bullet : public Object
  {
  public:
    GameData::Bullet _data;
    int idUnit;
    Bullet(World& w, int id, int damage, int idU) : Object(w, Object::Bullet, id), _data(damage, id), idUnit(idU) {}
    ~Bullet();
    virtual b2Body* setBody(float angle, b2Vec2 position, BitField * b);
    /// TODO: implement these functions (or delete all serialized related stuff (nah..))
    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
    virtual int	getClassId() const {return 0;}
  private:
    void intraCollision(Object *o);
    void intraCollisionUnit(Object *o);
    void intraCollisionBullet(Object *o);
    void intraCollisionElement(Object *o);
  };
}

#endif
