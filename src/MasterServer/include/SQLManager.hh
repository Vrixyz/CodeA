#ifndef _LOGIN_HH_
#define _LOGIN_HH_

#include <iostream>
#include <sqlite3.h>

#include <stdio.h>
#include <stdlib.h>

#include "User.hh"

class SQLManager
{
private:
  std::string	_name;
  sqlite3	*_db;

  int tmp_win;
public:
  SQLManager();
  ~SQLManager();
  int coDB();
  void dcDB();
  int delElem();
  User *findUser(std::string, std::string);
  int insertElem(std::string, std::string);
  sqlite3 *getDB();
  sqlite3 **getPtrDB();
  int createUsersTable();

  int modifElem(User*);
  User *returnStats(sqlite3_stmt*, std::string);
};

#endif
