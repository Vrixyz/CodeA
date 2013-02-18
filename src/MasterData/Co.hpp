#ifndef MASTER_DATA_CO_HPP
# define MASTER_DATA_CO_HPP

#include <msgpack.hpp>

namespace MasterData
{
  struct	CoClient
  {
    CoClient(std::string _login, std::string _pass) :
      login(_login), pass(_pass) {}
    std::string	login;
    std::string	pass;
    
    MSGPACK_DEFINE(login, pass);
  };
}

#endif
