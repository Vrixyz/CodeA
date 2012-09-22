//
// Serializable.hpp for  in /home/berger_t/PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 09:55:13 2012 thierry berger
// Last update Thu Sep 13 15:54:06 2012 thierry berger
//

#ifndef GAME_DATA_SERIALIZABLE_HPP
# define GAME_DATA_SERIALIZABLE_HPP

#include <msgpack.hpp>

namespace GameData
{
  class	Serializable
  {
  public:
    virtual void	serialize(msgpack::packer<msgpack::sbuffer>& packet) const = 0;
    virtual bool unSerialize(msgpack::packer<msgpack::sbuffer>& packet) = 0;
    virtual int	getClassId() const = 0;
  };
}

#endif
