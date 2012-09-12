//
// GameData.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:10:56 2012 thierry berger
// Last update Wed Sep 12 09:55:07 2012 thierry berger
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

///
/// \file GameData.hpp
/// \brief How data is stored and sent online.
/// \author Thierry.B
/// \version 0.1
/// \date 11 septembre 2012
/// 
/// A biggest form of data to be sent would be composed of these objects :
/// 
/// Type
/// World
/// Physics (of that 'World')
/// Unit
/// Physics (of that 'Unit')
/// [more Unit and Physics]
/// Element
/// Physics (of that 'Element')
/// [more Element and Physics]
///

namespace GameData
{
  struct Information {}; /// Empty mother class to go in a std::List<Information>
  typedef enum e_Type {
    Command,
    World
  } Type;
  struct	Command;
  struct	Element;
  struct	Unit;
  struct	World;
  struct	Physics;
  class		Serializable;
}

#include "Command.hpp"
#include "Element.hpp"
#include "Unit.hpp"
#include "World.hpp"
#include "Physics.hpp"
#include "Serializable.hpp"

#endif
