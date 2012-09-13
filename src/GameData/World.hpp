//
// World.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:39:26 2012 thierry berger
// Last update Thu Sep 13 15:39:16 2012 thierry berger
//

#ifndef GAME_DATA_WORLD_HPP
# define GAME_DATA_WORLD_HPP

#include <stdint.h>
#include <msgpack.hpp>

namespace GameData
{
  struct World
  {
    uint32_t	nbUnit;
    uint32_t	nbElement;
    uint32_t	nbBullet;
    
    MSGPACK_DEFINE(nbUnit, nbElement, nbBullet);
  };
}

#endif
