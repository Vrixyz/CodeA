//
// Element.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:16:58 2012 mathieu leurquin
// Last update Thu Sep 13 15:54:05 2012 thierry berger
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
    const GameData::Element& getData()const {return _data;}

    virtual void serialize(msgpack::packer<msgpack::sbuffer>& packet) const {return;}
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) {return false;}
    virtual int	getClassId() const {return 0;}
  };
}

#endif
