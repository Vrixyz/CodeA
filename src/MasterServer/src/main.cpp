#include "./../include/Define.hh"

void	step (int i)
{
  printf("step : ");
  switch (i)
    {
    case SQLITE_DONE:
      printf ("ok ");
      break;
    case SQLITE_BUSY:
      printf ("oqp ");
      break;
    case SQLITE_ERROR:
      printf ("err ");
      break;
    case SQLITE_ROW:
      printf ("row ");
      break;
    case SQLITE_MISUSE:
      printf ("mis ");
      break;
    default:
      printf ("??? ");
    }
  printf("\n");
     
}
     
int	callback(void *lokis, int nbCol, char **data, char **nomCol)
{
  for (int i = 0; i < nbCol; i++)
    {
      printf ("%s \t", data[i]);
    }
  printf ("\n");
  return 0;
}

int	main(int argc, char **argv)
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open ("bdd.db", &db);
  if (rc)
    {
      fprintf (stderr, "Can't open database: %s\n", sqlite3_errmsg (db));
      sqlite3_close (db);
      exit (1);
    }

  /*-------------------------------- Créer une table ---------------------------*/
  // char *requete0 = "CREATE TABLE table1 (id INTEGER, login varchar(30), pass varchar(30));";
  // if (sqlite3_exec (db, requete0, callback, 0, &zErrMsg) != SQLITE_OK)
  //   {
  //     printf ("0:(\n");
  //   }

  /*------------------------------- Créer un enregistrement première méthode ---*/
  // char *requete1 = "INSERT INTO table1 values (0, 'trax', 'plop');";
  // if (sqlite3_exec (db, requete1, callback, 0, &zErrMsg) != SQLITE_OK)
  //   {
  //     printf ("1:(\n");
  //   }

  /*------------------------------- Créer un enregistrement deuxième méthode ---*/
  // char *requete2 = "INSERT INTO table1 values(?, ?, ?);";
  // sqlite3_stmt *stmt = NULL;
  // if (sqlite3_prepare_v2 (db, requete2, 50, &stmt, NULL) != SQLITE_OK)
  //   {
  //     printf ("2:(\n");
  //   }
     
  // sqlite3_bind_int (stmt, 1, 42);
  // sqlite3_bind_text (stmt, 2, "traxou", 7, NULL);
  // sqlite3_bind_text (stmt, 3, "plip", 5, NULL);
  // step(sqlite3_step(stmt));
  // sqlite3_reset (stmt);     
     
  /*------------------------------- Lecture d'enregistrement -------------------*/
  std::string requete3 = "SELECT * FROM table1;";
  if (sqlite3_exec (db, requete3.c_str(), callback, 0, &zErrMsg) != SQLITE_OK)
    {
      printf ("3:(\n");
    }
     
  sqlite3_close (db);
  return 0;
}
