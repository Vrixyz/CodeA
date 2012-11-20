//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Wed Nov  7 15:08:08 2012 mathieu leurquin
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

#include <msgpack.hpp>

namespace GameData
{
  namespace Command
  {
    typedef enum e_Id
      {
	Fire = 0,
	AimTo = 1,
	MoveTo = 2, /// for RTS
	Move = 3,
	RotateLeft = 4,
	RotateRight = 5,
	RotateStop = 6,
	Shield = 7,
	BePlayer = 8
      } Id;
  }
}

#endif
