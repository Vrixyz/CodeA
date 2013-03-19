#ifndef _USER_HH_
#define _USER_HH_

#include <iostream>
#include "Socket.hh"
#include "GameServer.hh"

class User
{
public:
  User(std::string);
  ~User();
  GameServer*	getServ(){return _game;}
  void		setServ(GameServer* s){_game = s;}
  Socket*	getSoc(){return _soc;}
  void		setSoc(Socket* soc){_soc = soc;}
  std::string	getName(){return _login;}
  bool		isInGame(){return _ig;}
  void		setIG(bool i){_ig = i;}
private:
  Socket*	_soc;
  std::string	_login;
  bool		_ig;
  GameServer*	_game;
};

#endif
