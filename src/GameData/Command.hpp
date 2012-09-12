//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Wed Sep 12 12:14:13 2012 thierry berger
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

namespace GameData
{
  struct Command : Information
  {
    Command() : x(0), y(0){}
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
      } Type type;
    float x;
    float y;
  };
}

#endif
