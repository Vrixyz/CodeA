//
// Unit.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:42:32 2012 thierry berger
// Last update Fri Sep 14 13:19:39 2012 thierry berger
//

#ifndef GAME_DATA_UNIT_HPP
# define GAME_DATA_UNIT_HPP

#include <stdint.h>
#include <list>
#include <msgpack.hpp>

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

    MSGPACK_DEFINE(playersId, id, health, aimRotation);
  };
}

#endif
