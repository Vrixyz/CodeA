#ifndef _USER_HH_
#define _USER_HH_

#include <iostream>
#include "Socket.hh"
#include "GameServer.hh"
#include "../../MasterData/Command.hpp"
#include "../../GameData/Command.hpp"

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

  /* Stats */
  int		games_win;
  int		games_win_1;
  int		games_win_2;
  int		games_played;
  int		games_played_1;
  int		games_played_2;
  std::string	succes;
private:
  Socket*	_soc;
  std::string	_login;
  bool		_ig;
  GameServer*	_game;
};

void		addStat(User*, MasterData::EndGame);
#endif
