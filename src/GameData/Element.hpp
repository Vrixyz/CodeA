//
// Element.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:08:47 2012 thierry berger
// Last update Wed Sep 12 16:17:30 2012 thierry berger
//

#ifndef GAME_DATA_ELEMENT_HPP
# define GAME_DATA_ELEMENT_HPP

#include <stdint.h>

namespace GameData
{
  struct Element
  {
    int		id;
    bool	walkable;

    Element(int _id, bool _walkable) : id(_id), walkable(_walkable) {};
  };
}

#endif
