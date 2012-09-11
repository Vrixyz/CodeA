//
// Unit.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:42:32 2012 thierry berger
// Last update Tue Sep 11 18:25:22 2012 thierry berger
//

#ifndef GAME_DATA_UNIT_HPP
# define GAME_DATA_UNIT_HPP

#include <stdint.h>

namespace GameData
{
  struct	Unit : Information
  {
    uint32_t	unitId;
    uint32_t	health;
    float	aimRotation;
  };
}

#endif
