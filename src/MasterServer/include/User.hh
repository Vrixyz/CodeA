#ifndef _USER_HH_
#define _USER_HH_

#include <iostream>
#include "Socket.hh"

class User
{
public:
  User(std::string);
  ~User();
  Socket*	getSoc(){return _soc;}
  void		setSoc(Socket* soc){_soc = soc;}
  std::string	getName(){return _login;}
  bool		isInGame(){return _ig;}
  /* Stats */
  int		games_win;
  int		games_win_1;
  int		games_win_2;
  int		games_played;
  int		games_played_1;
  int		games_played_2;
private:
  Socket*	_soc;
  std::string	_login;
  bool		_ig;
};

#endif
