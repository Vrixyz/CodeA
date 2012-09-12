//
// Element.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:16:58 2012 mathieu leurquin
// Last update Wed Sep 12 13:28:59 2012 mathieu leurquin
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
    
    GameData::Element getData();
  };
}

#endif
