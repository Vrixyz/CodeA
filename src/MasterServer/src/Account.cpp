#include "Account.hpp"

Account::Account(std::string login, std::string pass, std::string mail, int succes, SQLManager *sql)
{
  _id = -1;
  _login = login;
  _pass = pass;
  _mail = mail;
  _succes = succes;
  _sql = sql;
}

Account::Account(int id, std::string login, std::string pass, std::string mail, int succes, SQLManager *sql)
{
  _id = id;
  _login = login;
  _pass = pass;
  _mail = mail;
  _succes = succes;
  _sql = sql;
}

bool Account::getId()
{
  sqlite3_stmt *stmt;
  std::string req;
  char * text;
  int id;
  int tryval;

  req = "SELECT id FROM Account WHERE login=?";
  _sql->prepare(req, &stmt);
  if (sqlite3_bind_text (stmt, 1, _login.data(), _login.length(), SQLITE_STATIC) == SQLITE_OK)
    if ((tryval = _sql->step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << _login << std::endl;
    else
      {
	text = (char *)(sqlite3_column_text (stmt, 0));
	std::stringstream(text) >> id;
	_id = id;
	_sql->clean(stmt);
	return true;
      }
  _sql->clean(stmt);
  return false;
}

bool Account::save()
{
  if (_id == -1)
    return insert();
  else
    return update();
}

bool Account::insert()
{
  sqlite3_stmt *stmt;
  std::string req;
  int tryval;

  req = "INSERT INTO Account(login, pass, mail, succes) VALUES(?, ?, ?, ?)";
  _sql->prepare(req, &stmt);
    if (sqlite3_bind_text (stmt, 1, _login.data(), _login.length(), SQLITE_STATIC) == SQLITE_OK)
      if (sqlite3_bind_text (stmt, 2, _pass.data(), _pass.length(), SQLITE_STATIC) == SQLITE_OK)
	if (sqlite3_bind_text (stmt, 3, _mail.data(), _mail.length(), SQLITE_STATIC) == SQLITE_OK)
	  if (sqlite3_bind_int (stmt, 4, _succes) == SQLITE_OK)
	    if ((tryval = _sql->step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
	      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << _login << std::endl << _pass << std::endl << _mail << std::endl << _succes << std::endl;
	    else
	      {
		_sql->clean(stmt);
		return getId();
	      }
    _sql->clean(stmt);
    return false;
}

bool Account::update()
{
  sqlite3_stmt *stmt;
  std::string req;
  int tryval;

  std::cout << "UPDATE" << std::endl;
  req = "UPDATE Account SET login=?, pass=?, mail=?, succes=? WHERE id=?";
  _sql->prepare(req, &stmt);
    if (sqlite3_bind_text (stmt, 1, _login.data(), _login.length(), SQLITE_STATIC) == SQLITE_OK)
      if (sqlite3_bind_text (stmt, 2, _pass.data(), _pass.length(), SQLITE_STATIC) == SQLITE_OK)
	if (sqlite3_bind_text (stmt, 3, _mail.data(), _mail.length(), SQLITE_STATIC) == SQLITE_OK)
	  if (sqlite3_bind_int (stmt, 4, _succes) == SQLITE_OK)
	    if (sqlite3_bind_int (stmt, 5, _id) == SQLITE_OK)
	      if ((tryval = _sql->step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
		std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << _login << std::endl << _pass << std::endl << _mail << std::endl << _succes << std::endl << _id << std::endl;
	      else
		{
		  _sql->clean(stmt);
		  return true;
		}
    _sql->clean(stmt);
    return false;
}

Account* tryConnect(std::string login, std::string pass, SQLManager *_sql)
{
  sqlite3_stmt *stmt;
  char * text;
  std::string req;
  int id;
  int succes;
  Account *acc;
  int tryval;

  req = "SELECT * FROM Account WHERE login=?";
  _sql->prepare(req, &stmt);
  if (sqlite3_bind_text (stmt, 1, login.data(), login.length(), SQLITE_STATIC) == SQLITE_OK)
    if ((tryval = _sql->step(stmt)) && tryval != SQLITE_ROW && tryval!= SQLITE_DONE && tryval != SQLITE_OK)
      std::cout << "SQL FAILURE IN:" << std::endl << req << std::endl << "WITH:" << std::endl << login << std::endl;
    else
      {
	if (tryval == SQLITE_ROW)
	  {
	    text = (char *)(sqlite3_column_text (stmt, 0));
	    std::stringstream(text) >> id;
	    text = (char *)(sqlite3_column_text (stmt, 4));
	    std::stringstream(text) >> succes;
	    if ((char *)(sqlite3_column_text (stmt, 2)) == pass)
	      acc = new Account(id, (char *)(sqlite3_column_text (stmt, 1)), (char *)(sqlite3_column_text (stmt, 2)), (char *)(sqlite3_column_text (stmt, 3)), succes, _sql);
	    else 
	      acc = NULL;
	    _sql->clean(stmt);
	    return acc;
	  }
	else
	  std::cout << "No row" << std::endl;
      }
  _sql->clean(stmt);
  return NULL;
}

void Account::set(std::string mdp)
{
  _pass = mdp;
}
