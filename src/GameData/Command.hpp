//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Wed Oct 10 11:51:04 2012 mathieu leurquin
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
	Fire,
	MoveTo, /// for RTS
	aimTo,
	Move
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
