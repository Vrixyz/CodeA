#ifndef _SQLM
#define _SQLM

#include <iostream>
#include "sqlite3.h"

class SQLManager
{
private:
  std::string _dbname;
  sqlite3 *_db;
  bool _valid;
public:
  SQLManager(std::string s);
  ~SQLManager();
  bool prepare(std::string, sqlite3_stmt **);
  int step(sqlite3_stmt *);
  void clean(sqlite3_stmt *);
  bool execute(std::string);
  bool isValid(){return (_valid);}
};

#endif //_SQLM
