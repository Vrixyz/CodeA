#ifndef MASTER_DATA_SERV_HPP
# define MASTER_DATA_SERV_HPP

#include <list>
#include <msgpack.hpp>

namespace MasterData
{
  struct	Serv
  {
    Serv(int _id, std::string _name) :
      id(_id), name(_name) {}
    int	id;
    std::string name;

    MSGPACK_DEFINE(id, name);
  };
}

#endif
