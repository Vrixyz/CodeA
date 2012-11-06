//
// BitField.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Tue Sep 18 10:58:04 2012 mathieu leurquin
// Last update Sat Nov  3 13:39:52 2012 mathieu leurquin
//

#ifndef SERVER_BITFIELD_HPP
# define SERVER_BITFIELD_HPP
#include <inttypes.h>
namespace Server
{
  class BitField
  {
  public:
    uint16_t what;
    uint16_t collide;
    enum cat {
      FRIENDLY_BULLET =	0x0001,
      ENNEMY_BULLET =	0x0002,  
      SHIELD_MAGE =     0x0004,
      FRIENDLY =	0x0006,
      ENNEMY =		0x0008,
      OBSTACLE =	0x0010,
      MAGE =		0x0012,
    };
    
    BitField(uint16_t w, uint16_t c) :  what(w), collide(c) {}
    void set(int position);
    void unset(int position);
    int get(int position);
  };
}

#endif
