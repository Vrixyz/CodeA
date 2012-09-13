//
// Physics.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:56:37 2012 thierry berger
// Last update Thu Sep 13 15:44:50 2012 thierry berger
//

#ifndef GAMEDATA_PHYSICS_HPP
# define GAMEDATA_PHYSICS_HPP

#include <msgpack.hpp>

namespace GameData
{
  struct Physics
  {
    float	x;
    float	y;
    float	s0x;
    float	s0y;
    float	s1x;
    float	s1y;
    float	s2x;
    float	s2y;
    float	s3x;
    float	s3y;

    MSGPACK_DEFINE(x, y, s0x, s0y, s1x, s1y, s2x, s2y,s3x, s3y);
  };
}

#endif
