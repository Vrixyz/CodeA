//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Sun Oct 28 11:27:46 2012 thierry berger
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

#include <msgpack.hpp>

namespace GameData
{
  struct Command
  {
    // make id command
    typedef enum e_Type
      {
	Fire = 0,
	MoveTo = 1, /// for RTS
	AimTo = 2,
	Move = 3
      } Type;
    int type;
    //

    float x;
    float y;
    Command() : x(0), y(0) {}
    Type getType(){return (Type)type;}
    MSGPACK_DEFINE(type, x, y);
  };
}

#endif
