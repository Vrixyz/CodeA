#include "./../include/Define.hh"
#include "./../include/SQLManager.hh"

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
      std::cout << data[i];
      std::cout << " ";
    }
  std::cout << std::endl;
  return 0;
}

void	*checkLogs(std::string toCheck)
{  
  SQLManager *test;
  char *zErrMsg = 0;
  int rc;

  test = new SQLManager();

  std::cout << "logs to check " << toCheck << std::endl;

  test->coDB();

  //  rc = test->splitAndCheck(toCheck);

  test->dcDB();

  return (NULL);
}
