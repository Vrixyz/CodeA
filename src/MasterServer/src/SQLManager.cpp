#include "./../include/SQLManager.hh"
#include "./../include/Define.hh"

SQLManager::SQLManager()
{
  _name = "dbb.db";
}

SQLManager::~SQLManager()
{
}

int	SQLManager::coDB()
{
  int rc;

  rc = sqlite3_open("bdd.db", &_db);
  if (rc)
    {
      std::cerr << "Can't open database: " << sqlite3_errmsg(this->_db) << std::endl;
      sqlite3_close(this->_db);
      return (-1);
    }
  return (1);
}

sqlite3	*SQLManager::getDB()
{
  return this->_db;
}

sqlite3	**SQLManager::getPtrDB()
{
  return &(this->_db);
}

void	SQLManager::dcDB()
{
  sqlite3_close(_db);
}

int	SQLManager::createUsersTable()
{
  char		*zErrMsg;
  std::string	requet0;

  requet0 = "CREATE TABLE user (";
  requet0 += "login varchar(30) unique,";
  requet0 += "pass varchar(30),";
  requet0 += "games_win int(10),";
  requet0 += "games_win_1 int(10),";
  requet0 += "games_win_2 int(10)";
  requet0 += "games_played int(10),";
  requet0 += "games_played_1 int(10),";
  requet0 += "games_played_2 int(10),";
  requet0 += ");";

  if (sqlite3_exec(_db, requet0.c_str(), 0, 0, &zErrMsg) != SQLITE_OK)
    {
      std::cerr << "[WARNING] Erreur dans la creation d'une table. (ou table deja creee)" << std::endl;
      return (-1);
    }
  return (0);
}

int	SQLManager::insertElem(std::string name, std::string pass)
{
  std::string	req;
  int		ret;
  sqlite3_stmt	*stmt;

  ret = 1;
  req = "INSERT INTO user values(?, ?, 0, 0, 0, 0, 0, 0);";
  stmt = NULL;
  if (sqlite3_prepare_v2(this->_db, req.c_str(), req.size(), &stmt, NULL) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans l'ajout d'un nouveau element." << std::endl;
      return -1;
    }
  sqlite3_bind_text(stmt, 1, name.c_str(), name.size(), NULL);
  sqlite3_bind_text(stmt, 2, pass.c_str(), pass.size(), NULL);
  ret = sqlite3_step(stmt);
  if (ret != SQLITE_ROW && ret != SQLITE_DONE && ret != SQLITE_OK)
    ret = -1;
  sqlite3_reset(stmt);    
  return ret; 
}

User	*SQLManager::findUser(std::string name, std::string pass)
{
  std::string   req;
  sqlite3_stmt  *stmt;
  int		s;

  req = "SELECT * FROM user WHERE login = ? AND pass = ?;";
  stmt = NULL;
  if (sqlite3_prepare_v2(this->_db, req.c_str(), 50, &stmt, NULL) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans la recuperation d'une utilisateur." << std::endl;
    }
  sqlite3_bind_text(stmt, 1, name.c_str(), name.size(), NULL);
  sqlite3_bind_text(stmt, 2, pass.c_str(), pass.size(), NULL);
  s = sqlite3_step(stmt);
  if (s == SQLITE_DONE)
    return (NULL);
  else if (s == SQLITE_ROW)
    return (returnStats(stmt, name));
  else
    return(NULL);
  return (NULL);
}

User	*SQLManager::returnStats(sqlite3_stmt *stmt, std::string login)
{
  User* toRet;

  toRet = new User(login);
  toRet->games_win = sqlite3_column_int(stmt, 2);
  toRet->games_win_1 = sqlite3_column_int(stmt, 3);
  toRet->games_win_2 = sqlite3_column_int(stmt, 4);
  toRet->games_played = sqlite3_column_int(stmt, 5);
  toRet->games_played_1 = sqlite3_column_int(stmt, 6);
  toRet->games_played_2 = sqlite3_column_int(stmt, 7);
  return (toRet);
}

int	SQLManager::modifElem(User* toEdit)
{
  std::string	req;
  int		ret;
  sqlite3_stmt	*stmt;

  ret = 1;
  req = "UPDATE user SET";
  req += " games_win = ?,";
  req += " games_win_1 = ?,";
  req += " games_win_2 = ?,";
  req += " games_played = ?,";
  req += " games_played_1 = ?,";
  req += " games_played_2 = ?";
  req += " WHERE login = ?;";
  stmt = NULL;
  if (sqlite3_prepare_v2(this->_db, req.c_str(), req.size(), &stmt, NULL) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans l'ajout d'un nouveau element." << std::endl;
      return -1;
    }
  sqlite3_bind_int(stmt, 1, toEdit->games_win);
  sqlite3_bind_int(stmt, 2, toEdit->games_win_1);
  sqlite3_bind_int(stmt, 3, toEdit->games_win_2);
  sqlite3_bind_int(stmt, 4, toEdit->games_played);
  sqlite3_bind_int(stmt, 5, toEdit->games_played_1);
  sqlite3_bind_int(stmt, 6, toEdit->games_played_2);
  sqlite3_bind_text(stmt, 7, toEdit->getName().c_str(), toEdit->getName().size(), NULL);
  ret = sqlite3_step(stmt);
  if (ret != SQLITE_ROW && ret != SQLITE_DONE && ret != SQLITE_OK)
    ret = -1;
  sqlite3_reset(stmt);    
  return ret;
}

int	SQLManager::delElem()
{

}
