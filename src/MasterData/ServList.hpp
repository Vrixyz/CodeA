#ifndef MASTER_DATA_SERV_HPP
# define MASTER_DATA_SERV_HPP

#include <list>
#include <msgpack.hpp>

namespace MasterData
{
  struct	Serv
  {
    int	id;
    std::string name;

    MSGPACK_DEFINE(id, name);
  };

  struct	ListServ
  {
    std::list<Serv> list;

    MSGPACK_DEFINE(list);
  };
}

#endif
