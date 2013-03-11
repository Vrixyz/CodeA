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
  std::string requete0 = "CREATE TABLE user (login varchar(30) unique, pass varchar(30), wins int(10));";

  if (sqlite3_exec(_db, requete0.c_str(), 0, 0, &zErrMsg) != SQLITE_OK)
    {
      std::cerr << "[WARNING] Erreur dans la creation d'une table. (ou table deja creee)" << std::endl;
      return (-1);
    }
  return (0);
}

int	SQLManager::insertElem(std::string name, std::string pass)
{
  std::string	req;

  int ret;
  sqlite3_stmt	*stmt;

  ret = 1;
  req = "INSERT INTO user values(?, ?, 0);";
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
  sqlite3_bind_text (stmt, 1, name.c_str(), name.size(), NULL);
  sqlite3_bind_text (stmt, 2, pass.c_str(), pass.size(), NULL);
  s = sqlite3_step(stmt);
  sqlite3_reset (stmt);
  if (s == SQLITE_DONE)
    return (NULL);
  else if (s == SQLITE_ROW)
    return (new User(name));
  else
    return(NULL);
  return (NULL);
  // while (1)
  //   {
  //     s = sqlite3_step (stmt);
  //     if (s == SQLITE_ROW) {
  // 	int bytes;
  // 	const unsigned char * text;
  // 	bytes = sqlite3_column_bytes(stmt, 0);
  // 	text  = sqlite3_column_text (stmt, 0);
  // 	printf ("%d: %s\n", row, text);
  // 	row++;
  //     }
  //     else if (s == SQLITE_DONE) {
  // 	break;
  //     }
  //     else {
  // 	fprintf (stderr, "Failed.\n");
  // 	exit (1);
  //     }
  //   }
}

int	SQLManager::modifElem(int nb_win, std::string name)
{
  std::string	req;
  int ret;
  sqlite3_stmt	*stmt;

  ret = 1;
  req = "UPDATE user win = ? WHERE login = ?;";
  stmt = NULL;
  if (sqlite3_prepare_v2(this->_db, req.c_str(), req.size(), &stmt, NULL) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans l'ajout d'un nouveau element." << std::endl;
      return -1;
    }
  sqlite3_bind_int(stmt, 1, nb_win);
  sqlite3_bind_text(stmt, 2, name.c_str(), name.size(), NULL);
  ret = sqlite3_step(stmt);
  if (ret != SQLITE_ROW && ret != SQLITE_DONE && ret != SQLITE_OK)
    ret = -1;
  sqlite3_reset(stmt);    
  return ret;
}

int	SQLManager::delElem()
{

}
