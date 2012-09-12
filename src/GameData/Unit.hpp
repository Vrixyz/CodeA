//
// Unit.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:42:32 2012 thierry berger
// Last update Wed Sep 12 13:49:42 2012 mathieu leurquin
//

#ifndef GAME_DATA_UNIT_HPP
# define GAME_DATA_UNIT_HPP

#include <stdint.h>

namespace GameData
{
  struct	Unit
  {
    uint32_t	id;
    uint32_t	health;
    float	aimRotation;
  };
}

#endif
