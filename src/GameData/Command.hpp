//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Thu Sep 13 20:01:00 2012 thierry berger
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

namespace GameData
{
  struct Command
  {
    typedef enum e_Type
      {
	Fire,
	MoveTo, /// for RTS
	aimTo,
	goUp,
	goRight,
	goDown,
	goLeft,
	stopUp,
	stopRight,
	stopDown,
	stopLeft
      } Type;
    Type type;
    float x;
    float y;
    Command() : x(0), y(0) {}
  };
}

#endif
