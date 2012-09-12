//
// Unit.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:42:32 2012 thierry berger
// Last update Wed Sep 12 16:23:34 2012 thierry berger
//

#ifndef GAME_DATA_UNIT_HPP
# define GAME_DATA_UNIT_HPP

#include <stdint.h>

namespace GameData
{
  struct	Unit
  {
    Unit(uint32_t _id, uint32_t _health) :
      id(_id), health(_health) {}
    uint32_t	id;
    uint32_t	health;
    float	aimRotation;
  };
}

#endif
