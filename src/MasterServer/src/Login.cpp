#include "./../include/Login.hh"
#include "./../include/Define.hh"

Login::Login()
{
  _name = "dbb.db";
}

Login::~Login()
{
}

int	Login::coDB()
{
  int rc;

  rc = sqlite3_open("bdd.db", &_db);
  if (rc)
    {
      std::cerr << "Can't open database: " << sqlite3_errmsg(this->_db) << std::endl;
      sqlite3_close(this->_db);
      exit (1);
    }
  return (1);
}

sqlite3	*Login::getDB()
{
  return this->_db;
}

sqlite3	**Login::getPtrDB()
{
  return &(this->_db);
}

void	Login::dcDB()
{
  sqlite3_close(_db);
}

int	Login::createUsersTable()
{
  char		*zErrMsg;
  std::string requete0 = "CREATE TABLE table1 (login varchar(30), pass varchar(30));";

  if (sqlite3_exec(_db, requete0.c_str(), 0, 0, &zErrMsg) != SQLITE_OK)
    {
      std::cerr << "[WARNING] Erreur dans la creation d'une table. (ou table deja creee)" << std::endl;
      return (-1);
    }
  return (0);
}

int	Login::insertElem(std::string name, std::string pass)
{
  std::string	req;
  sqlite3_stmt	*stmt;

  req = "INSERT INTO table1 values(?, ?);";
  stmt = NULL;
  if (sqlite3_prepare_v2(this->_db, req.c_str(), 50, &stmt, NULL) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans l'ajout d'un nouveau element." << std::endl;
    }
  sqlite3_bind_text (stmt, 1, name.c_str(), name.size(), NULL);
  sqlite3_bind_text (stmt, 2, pass.c_str(), pass.size(), NULL);
  step(sqlite3_step(stmt));
  sqlite3_reset (stmt);     
}

int	Login::printLog()
{
  char		*zErrMsg;
  std::string	requete = "SELECT * FROM table1;";

  std::cout << "Logs contenus dans la base de donnees :" << std::endl;
  if (sqlite3_exec(_db, requete.c_str(), callback, 0, &zErrMsg) != SQLITE_OK)
    {
      std::cerr << "[ERROR] Erreur dans lors du retour des login/passw." << std::endl;
      return (-1);
    }
  std::cout << std::endl;
  return (0);
}

User	*Login::findUser(std::string name, std::string pass)
{
  std::string   req;
  sqlite3_stmt  *stmt;
  int		s;

  req = "SELECT * FROM table1 WHERE login = ? AND pass = ?;";
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
    return (new User(name, 0));
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

int	Login::modifElem()
{

}

int	Login::delElem()
{

}
