#ifndef MASTER_DATA_SERIALIZABLE_HPP
# define MASTER_DATA_SERIALIZABLE_HPP

#include <msgpack.hpp>

namespace MasterData
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
