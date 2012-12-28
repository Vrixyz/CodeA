//
// BitField.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Tue Sep 18 10:58:04 2012 mathieu leurquin
// Last update Tue Dec 18 16:22:50 2012 mathieu leurquin
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
      OBSTACLE       = 1,
      TEAM2_BULLET   = 2,  
      TEAM2_SHIELD   = 4,
      TEAM2_UNIT     = 8,
      TEAM1_BULLET   = 16,
      TEAM1_SHIELD   = 32,
      TEAM1_UNIT     = 64,
    };
    
    BitField(uint16_t w, uint16_t c) :  what(w), collide(c) {}
    void set(int position);
    void unset(int position);
    int get(int position);
  };
}

#endif
