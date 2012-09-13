//
// Unit.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:42:32 2012 thierry berger
// Last update Thu Sep 13 13:27:55 2012 thierry berger
//

#ifndef GAME_DATA_UNIT_HPP
# define GAME_DATA_UNIT_HPP

#include <stdint.h>
#include <list>

namespace GameData
{
  struct	Unit
  {
    Unit(uint32_t _id, uint32_t _health) :
      id(_id), health(_health) {}
    std::list<uint32_t> playersId;
    uint32_t	id;
    uint32_t	health;
    float	aimRotation;
  };
}

#endif
