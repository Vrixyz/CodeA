#ifndef MASTER_DATA_CO_HPP
# define MASTER_DATA_CO_HPP

#include <msgpack.hpp>

namespace MasterData
{
  //SYNTHAXE DE CO CLIENT
  struct	CoClient
  {
    CoClient(std::string _login, std::string _pass) :
      login(_login), pass(_pass) {}
    std::string	login;
    std::string	pass;
    
    MSGPACK_DEFINE(login, pass);
  };

  //SYNTHAXE DE CO GAME SERVER
  struct	CoServer
  {
    CoServer(int _port, std::string _name) :
      port(_port), name(_name) {}
    int		port;
    std::string	name;
    
    MSGPACK_DEFINE(port, name);
  };

  //SYNTHAXE DE REGISTER
  struct	RegClient
  {
    RegClient(std::string _login, std::string _pass) :
      login(_login), pass(_pass) {}
    std::string	login;
    std::string	pass;
    
    MSGPACK_DEFINE(login, pass);
  };

  //ENVOI D'INFOS AU CLIENT SUR SON COMPTE(USEFULL POUR LE MOMENT)
  struct	InfosClient
  {
    InfosClient(std::string _name) :
      name(_name) {}
    std::string name;
    
    MSGPACK_DEFINE(name);
  };

  // INFOS SERVEUR
  struct	InfosServer
  {
    InfosServer(std::string _ip, int _port) :
      ip(_ip), port(_port) {}
    std::string ip;
    int		port;

    MSGPACK_DEFINE(ip, port);
  };

  // INFOS PLAYER
  struct	InfosPlayer
  {
    InfosPlayer(std::string _ip, std::string _name) :
      ip(_ip), name(_name) {}
    std::string ip;
    std::string name;
    
    MSGPACK_DEFINE(ip, name);
  };
}

#endif
