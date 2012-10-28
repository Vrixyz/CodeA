#include "GameAccountManager.hpp"
#include <sstream>

GameAccountManager::GameAccountManager()
{
  _db = NULL;
  _dbname = "CoG.db";
}

bool GameAccountManager::reset()
{
  int tryval;
  std::string requete;

  if (_db != NULL)
    sqlite3_close(_db);
  tryval = sqlite3_open(_dbname.data(), &_db);
  if (tryval == SQLITE_OK)
    {
      requete = "CREATE TABLE IF NOT EXISTS Account(";
      requete += "id integer primary key autoincrement, ";
      requete += "login varchar(50) unique, ";
      requete += "pass varchar(50), ";
      requete += "mail varchar(50), ";
      requete += "succes text";
      requete +=") ;";
      tryval = sqlite3_exec(_db, requete.data(), 0, 0, NULL);
      if(tryval == SQLITE_OK)
	return true;
      sqlite3_close(_db);
    }
  _db = NULL;
  return false;
}

IAccount<std::string>* GameAccountManager::createAccount(const std::string& login,const std::string& pass, const std::string&mail)
{
  sqlite3_stmt *stmt;
  std::string req;
  int tryval;
  IAccount<std::string>* acc;
  
  req = "INSERT INTO Account(login, pass, mail, succes) VALUES(?, ?, ?, ?)";
  sqlite3_prepare_v2(_db, req.data(), -1, &stmt, NULL);
  if (sqlite3_bind_text (stmt, 1, login.data(), login.length(), SQLITE_STATIC) == SQLITE_OK)
    if (sqlite3_bind_text (stmt, 2, pass.data(), pass.length(), SQLITE_STATIC) == SQLITE_OK)
      if (sqlite3_bind_text (stmt, 3, mail.data(), mail.length(), SQLITE_STATIC) == SQLITE_OK)
	if (sqlite3_bind_text (stmt, 4, "", 0, SQLITE_STATIC) == SQLITE_OK)
	  if ((tryval = sqlite3_step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
	    std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << login << std::endl << pass << std::endl << mail << std::endl << "" << std::endl;
	  else
	    {
	      sqlite3_step(stmt);
	      acc = new GameAccount();
	      acc->setLogin(login);
	      acc->setPasswd(pass);
	      acc->setMailAddress(mail);
	      return getId(login, acc);
	    }
  sqlite3_finalize(stmt);
  return NULL;
}

IAccount<std::string>*	GameAccountManager::getId(const std::string& login, IAccount<std::string>* acc)
{
  sqlite3_stmt *stmt;
  std::string req;
  char * text;
  int id;
  int tryval;

  req = "SELECT id FROM Account WHERE login=?";
  sqlite3_prepare_v2(_db, req.data(), -1, &stmt, NULL);
  if (sqlite3_bind_text (stmt, 1, login.data(), login.length(), SQLITE_STATIC) == SQLITE_OK)
    if ((tryval = sqlite3_step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << login << std::endl;
    else
      {
	if (tryval == SQLITE_ROW)
	  {
	    text = (char *)(sqlite3_column_text (stmt, 0));
	    std::stringstream(text) >> id;
	    acc->setId(id);
	    sqlite3_finalize(stmt);
	    return acc;
	  }
      }
  sqlite3_finalize(stmt);
  return NULL;
}

bool GameAccountManager::deleteAccount(const IAccount<std::string>& account)
{
  sqlite3_stmt *stmt;
  std::string req;
  int tryval;

  req = "DELETE FROM Account WHERE id=?";
  sqlite3_prepare_v2(_db, req.data(), -1, &stmt, NULL);
  if (sqlite3_bind_int (stmt, 1, account.getId()) == SQLITE_OK)
    if ((tryval = sqlite3_step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << account.getId() << std::endl;
    else
      {
	sqlite3_finalize(stmt);
	return true;
      }
  sqlite3_finalize(stmt);
  return false;
}

bool GameAccountManager::updateAccount(const IAccount<std::string>& account)
{
  sqlite3_stmt *stmt;
  std::string req;
  int tryval;

  req = "UPDATE Account SET login=?, pass=?, mail=?, succes=? WHERE id=?";
  sqlite3_prepare_v2(_db, req.data(), -1, &stmt, NULL);
  if (sqlite3_bind_text (stmt, 1, account.getLogin().data(), account.getLogin().length(), SQLITE_STATIC) == SQLITE_OK)
    if (sqlite3_bind_text (stmt, 2, account.getPasswd().data(), account.getPasswd().length(), SQLITE_STATIC) == SQLITE_OK)
      if (sqlite3_bind_text (stmt, 3, account.getMailAddress().data(), account.getMailAddress().length(), SQLITE_STATIC) == SQLITE_OK)
	if (sqlite3_bind_text (stmt, 4, account.getData().data(), account.getData().length(), SQLITE_STATIC) == SQLITE_OK)
	  if (sqlite3_bind_int (stmt, 5, account.getId()) == SQLITE_OK)
	    if ((tryval = sqlite3_step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
	      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << account.getLogin() << std::endl << account.getPasswd() << std::endl << account.getMailAddress() << std::endl << account.getData() << std::endl << account.getId() << std::endl;
	    else
	      {
		sqlite3_finalize(stmt);
		return true;
	      }
  sqlite3_finalize(stmt);
  return false;
}

IAccount<std::string>* GameAccountManager::tryConnect(const std::string&login, const std::string& pass)
{
  return NULL;
}

IAccount<std::string>* GameAccountManager::getAccountById(int id)
{
  return NULL;
}
