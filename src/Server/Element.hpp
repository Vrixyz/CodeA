//
// Element.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:16:58 2012 mathieu leurquin
// Last update Fri Sep 14 10:33:57 2012 thierry berger
//

#ifndef SERVER_ELEMENT_HPP
# define SERVER_ELEMENT_HPP

#include "../GameData/Element.hpp"
#include "Object.hpp"

namespace Server
{
  class	Element : public Object
  {
  public:
    GameData::Element _data;
    
    Element(World& world, int id, bool walkable) :
      Object(world, Object::Element, id), _data(id, walkable) {}
    virtual b2Body* setBody(float width = 100, float height = 100);
    const GameData::Element& getData()const {return _data;}

    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet);
    virtual int	getClassId() const;
  };
}

#endif
