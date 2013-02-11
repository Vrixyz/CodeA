#include "SQLManager.hpp"

SQLManager::SQLManager(std::string name)
{
  int tryval;
  std::string requete;

  _dbname = name;
  tryval = sqlite3_open(_dbname.data(), &_db);
  if (tryval)
    _valid = false;
  else
    {
      _valid = true;

      requete = "CREATE TABLE IF NOT EXISTS Account(";
      requete += "id integer primary key autoincrement, ";
      requete += "login varchar(50) unique, ";
      requete += "pass varchar(50), ";
      requete += "mail varchar(50), ";
      requete += "succes integer";
      requete +=") ;";

      tryval = sqlite3_exec(_db, requete.data(), 0, 0, NULL);
      if(tryval != SQLITE_OK)
	_valid = false;
    }
}

bool SQLManager::execute(std::string requete)
{
  if (sqlite3_exec(_db, requete.data(), 0, 0, NULL) == SQLITE_OK)
    return true;
  return false;
}

bool SQLManager::prepare(std::string requete, sqlite3_stmt **statement)
{
  if (sqlite3_prepare_v2(_db, requete.data(), -1, statement, NULL) == SQLITE_OK)
    return true;
  return false;
}

int SQLManager::step(sqlite3_stmt *statement)
{
  return sqlite3_step(statement);
}

void SQLManager::clean(sqlite3_stmt *statement)
{
  sqlite3_finalize(statement);
}

SQLManager::~SQLManager()
{
  sqlite3_close(_db);
}
