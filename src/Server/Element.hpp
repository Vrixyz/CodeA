//
// Element.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:16:58 2012 mathieu leurquin
// Last update Sat Mar  2 13:20:10 2013 mathieu leurquin
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
    int _idU;
    GameData::Element _data;
    Element(World& world, bool walkable, int idU);
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
