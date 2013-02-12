#include "./../include/Define.hh"
#include "./../include/Login.hh"

int	step(int i)
{
  printf("[STEP] ");
  switch (i)
    {
    case SQLITE_DONE:
      std::cout << "OK" << std::endl;
      return (1);
      break;
    case SQLITE_BUSY:
      std::cout << "BUSY" << std::endl;
      return (-1);
      break;
    case SQLITE_ERROR:
      std::cout << "ERROR" << std::endl;
      return (-1);
      break;
    case SQLITE_ROW:
      std::cout << "ROW" << std::endl;
      return (-1);
      break;
    case SQLITE_MISUSE:
      std::cout << "MISUSE" << std::endl;
      return (-1);
      break;
    default:
      std::cout << std::endl;
      return (1);
    }
  std::cout << std::endl;
     
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
  Login *test;
  char *zErrMsg = 0;
  int rc;

  test = new Login();

  test->coDB();
  test->createUsersTable();
  test->insertElem("toto42", "titi42");
  test->insertElem("toto77", "titi77");
  test->insertElem("toto33", "titi33");
  test->printLog();
  test->dcDB();

  return 0;
}
