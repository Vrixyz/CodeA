//
// Physics.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:56:37 2012 thierry berger
// Last update Thu Sep 13 17:18:56 2012 thierry berger
//

#ifndef GAMEDATA_PHYSICS_HPP
# define GAMEDATA_PHYSICS_HPP

#include <msgpack.hpp>

namespace GameData
{
  struct Physics
  {
    struct Coord
    {
      float x;
      float y;

      Coord(float _x, float _y) : x(_x), y(_y) {}
      Coord() : x(0), y(0) {}

      MSGPACK_DEFINE(x, y);
    };
    float	x;
    float	y;
    std::list<Coord> vertices;

    MSGPACK_DEFINE(x, y, vertices);
  };
}

#endif
