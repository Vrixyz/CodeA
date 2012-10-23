#ifndef _ACCOUNT
#define _ACCOUNT

#include "SQLManager.hpp"
#include <sstream>

class Account
{
private:
  SQLManager *_sql;
  int	_id;
  int _succes;
  std::string _mail;
  std::string _pass;
  std::string _login;
  bool	insert();
  bool	update();
  bool	getId();
public:
  Account(int id, std::string login, std::string pass, std::string mail, int succes, SQLManager *_sql);
  Account(std::string login, std::string pass, std::string mail, int succes, SQLManager *_sql);
  ~Account();
  bool	save();
  void	set(std::string);
};

Account* tryConnect(std::string login, std::string pass, SQLManager *_sql);

#endif //_ACCOUNT
