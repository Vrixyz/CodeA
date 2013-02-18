#ifndef _USER_HH_
#define _USER_HH_

#include <iostream>

class User
{
public:
  User(std::string, int);
  ~User();
private:
  std::string	_login;
  int		_id;
};

#endif
