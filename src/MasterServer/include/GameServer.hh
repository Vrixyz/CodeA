#ifndef _GAMESERVER_HH_
#define _GAMESERVER_HH_

#include <iostream>
#include "Socket.hh"

#define MAXPLACE 2

class GameServer
{
public:
  GameServer(int, std::string, int);
  ~GameServer();
  Socket*	getSoc(){return _soc;}
  void		setSoc(Socket* soc){_soc = soc;}
  int		getId(){return _id;}
  std::string	getName(){return _name;}
  void		addPlayer(){_player ++;}
  int		getPlayer(){return _player;}
  int		getFree(){return (MAXPLACE - _player);}
private:
  Socket*	_soc;
  int		_port;
  int		_id;
  int		_player;
  std::string	_name;
};

#endif	
