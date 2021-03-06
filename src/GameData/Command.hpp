//
// Command.hpp for  in /home/berger_t//PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Sep 11 15:03:16 2012 thierry berger
// Last update Tue Apr  2 18:09:53 2013 mathieu leurquin
//

#ifndef GAME_DATA_HPP
# define GAME_DATA_HPP

#include <msgpack.hpp>

namespace GameData
{
  // we should always pluralize namespaces.
  namespace Command
  {
    typedef enum e_Id
      {
	Fire = 9,
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
  // "Command" would have been a better name, but I'm lazy to change the enum namespace.
  namespace CommandStruct
  {
    typedef int Unused;

    // NOTE: not used (yet?)
    struct Fire
    {
      int x;
      int y;
      int idUnit;
      
      MSGPACK_DEFINE(x, y, idUnit)
    };

    // AimTo not implemented
    struct Aim
    {
      int idUnit;
      
      MSGPACK_DEFINE(idUnit)
    };
    
    // MoveTo :
    struct MoveTo
    {
      int x;
      int y;
      std::list<unsigned int> idUnits;
      
      MSGPACK_DEFINE(x, y, idUnits)
    };

    struct Move
    {
      int x;
      int y;
      int idUnit;
      
      MSGPACK_DEFINE(x, y, idUnit)
    };

    // No args for Rotation* (yet?)
    struct Rotate
    {
      int idUnit;
      
      MSGPACK_DEFINE(idUnit)
    };

    // No args for Shield (yet?)
    struct Shield
    {
      int idUnit;
      
      MSGPACK_DEFINE(idUnit)
    };

    // // No args for BePlayer (yet?)
    struct BePlayer
    {
      typedef enum e_player_class
	{
	  INVOKER,
	  MAGE
	} player_class;

      std::string login;
      int type;

      MSGPACK_DEFINE(login, type)
    };

  }
}



#endif
