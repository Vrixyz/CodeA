//
// Serializable.hpp for  in /home/berger_t/PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 09:55:13 2012 thierry berger
// Last update Wed Sep 12 18:04:05 2012 thierry berger
//

#ifndef GAME_DATA_SERIALIZABLE_HPP
# define GAME_DATA_SERIALIZABLE_HPP

namespace GameData
{
  class	Serializable
  {
  public:
    virtual void*	serialize(int& finalLength) const = 0;
    /// overload that function please. (unserialized should be nulled (original value will be lost))
    static bool unSerialize(void* const serialized, void*& unserialized) {return false;}; 
    virtual int	getClassId() const = 0;
  };
}

#endif
