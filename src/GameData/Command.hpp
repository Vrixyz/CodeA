//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Mon Nov  5 12:32:57 2012 mathieu leurquin
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

#include <msgpack.hpp>

namespace GameData
{
  struct Command
  {
    typedef enum e_Type
      {
	Fire = 0,
	MoveTo = 1, /// for RTS
	RotateLeft = 2,
	RotateRight = 3,
	RotateStop = 4,
	Move = 5,
	Shield = 6
      } Type;
    int type;
    float x;
    float y;
    Command() : x(0), y(0) {}
    Type getType(){return (Type)type;}
    MSGPACK_DEFINE(type, x, y);
  };
}

#endif
