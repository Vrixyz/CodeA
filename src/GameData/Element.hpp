//
// Element.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:08:47 2012 thierry berger
// Last update Tue Sep 11 16:00:04 2012 thierry berger
//

#ifndef GAME_DATA_ELEMENT_HPP
# define GAME_DATA_ELEMENT_HPP

#include <stdint.h>

namespace GameData
{
  struct Element
  {
    bool	walkable;
    bool	dieAtContact;
    uint32_t	contactDamage; /// damage applied to element colliding with it.
  };
}

#endif
