//
// GameData.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 14:10:56 2012 thierry berger
// Last update Tue Apr  2 18:09:53 2013 mathieu leurquin
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
/// Type (not implemented) \n
/// World \n
/// Physics (of that 'World') \n
/// Unit \n
/// Physics (of that 'Unit') \n
/// [more Unit and Physics] \n
/// Element \n
/// Physics (of that 'Element') \n
/// [more Element and Physics] \n
/// Bullet \n
/// Physics (of that 'Bullet') \n
/// [more Bullet and Physics] \n
///

namespace GameData
{
  typedef enum e_Type {
    Command,
    World
  } Type;
  struct	Command;
  struct	Element;
  struct	Bullet;
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
#include "Bullet.hpp"

#endif
