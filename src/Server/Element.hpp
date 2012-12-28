//
// Element.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:16:58 2012 mathieu leurquin
// Last update Wed Dec 12 10:35:56 2012 mathieu leurquin
//

#ifndef SERVER_ELEMENT_HPP
# define SERVER_ELEMENT_HPP

#include "../GameData/Element.hpp"
#include "Object.hpp"
#include "BitField.hpp"

namespace Server
{
  class	Element : public Object
  {
  public:
    GameData::Element _data;
    int idUnit;
    Element(World& world, int id, bool walkable, int idU) :
      Object(world, Object::Element, id), _data(id, walkable), idUnit(idU) {}
    ~Element();
    virtual b2Body* setBody(BitField *b, float width = 100, float height = 100, int x = 10, int y = 10);
    const GameData::Element& getData()const {return _data;}

    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet);
    virtual int	getClassId() const;
  private:
    void intraCollision(Object *o);
    void intraCollisionUnit(Object *o);
    void intraCollisionBullet(Object *o);
    void intraCollisionElement(Object *o);
  };
}

#endif
