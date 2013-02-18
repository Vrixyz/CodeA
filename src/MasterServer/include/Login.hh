#ifndef _LOGIN_HH_
#define _LOGIN_HH_

#include <iostream>
#include <sqlite3.h>

#include <stdio.h>
#include <stdlib.h>

#include "User.hh"

class Login
{
private:
  std::string	_name;
  sqlite3	*_db;
public:
  Login();
  ~Login();
  int coDB();
  void dcDB();
  int delElem();
  int printLog();
  User *findUser(std::string, std::string);
  int modifElem();
  int insertElem(std::string, std::string);
  sqlite3 *getDB();
  sqlite3 **getPtrDB();
  int createUsersTable();
};

#endif
