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
  std::cout << "Logs contenus dans la base de donnees :" << std::endl;
  for (int i = 0; i < nbCol; i++)
    {
      std::cout << "!" << data[i] << "!" << std::endl;
    }
  std::cout << std::endl;
  return 0;
}

void	*checkLogs(std::string toCheck)
{  
  Login *test;
  char *zErrMsg = 0;
  int rc;

  test = new Login();

  std::cout << "logs to check " << toCheck << std::endl;

  test->coDB();

  rc = test->splitAndCheck(toCheck);

  test->dcDB();

  return (NULL);
}
