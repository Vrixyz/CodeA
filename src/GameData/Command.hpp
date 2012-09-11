//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Tue Sep 11 15:56:23 2012 thierry berger
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

namespace GameData
{
  struct Command
  {
    Command() : x(0), y(0){}
    typedef enum e_Type
      {
	Fire,
	MoveTo,
	aimTo,
	goUp,
	goRight,
	goDown,
	goLeft
      } Type type;
    float x;
    float y;
  };
}

#endif
