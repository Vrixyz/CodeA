#ifndef _GAMESERVER_HH_
#define _GAMESERVER_HH_

#include <iostream>
#include "Socket.hh"

class GameServer
{
public:
  GameServer(int, std::string, int);
  ~GameServer();
  Socket*	getSoc(){return _soc;}
  void		setSoc(Socket* soc){_soc = soc;}
  int		getId(){return _id;}
  std::string	getName(){return _name;}
private:
  Socket*	_soc;
  int		_port;
  int		_id;
  std::string	_name;
};

#endif
