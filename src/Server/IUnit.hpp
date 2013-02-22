//
// IUnit.hpp for  in /home/berger_t/Documents/CodeA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Jan 02 13:00:00 2013 thierry berger
// Last update Thu Feb 21 15:57:31 2013 mathieu leurquin
//

#ifndef SERVER_I_UNIT_HPP_
# define SERVER_I_UNIT_HPP_

#include "Player.hpp"
#include "Object.hpp"

namespace Server
{
  class IUnit : public Object
  {
  public:
    IUnit(World& w, int id) : Object(w, Object::Unit, id) {}
    virtual ~IUnit() {}
    virtual void addPlayer(Player* p) = 0;
    virtual bool belongsToPlayer(int idPlayer) const = 0;

    // NOTE: we had once parameters as (int x, int y). This solution is better for maintenance.
    virtual void setMove(const GameData::CommandStruct::Move& arg) = 0;

    // FIXME: a solo rotate command taking a parameter for [left/right/stop] would be pertinent.
    virtual void setRotateLeft() = 0;
    virtual void setRotateRight() = 0;
    virtual void setRotateStop() = 0;

    virtual void spell1(const GameData::CommandStruct::Fire& arg) = 0;
    virtual void spell2(const GameData::CommandStruct::Shield arg) = 0;
  };
}

# endif // SERVER_I_UNIT_HPP_
