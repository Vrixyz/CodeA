#include "SQLManager.hpp"
#include "Account.hpp"
#include "Error.h"

#include <stdio.h>
#include <stdlib.h>

void	run()
{
  SQLManager *_SQL;
  Account *titi;
  _SQL = new SQLManager("cog.db");
  if (!_SQL->isValid())
    {
      throw ERROR_1;
    }
  if ((titi = tryConnect("titi", "toti", _SQL)) != NULL)
    {
      std::cout << "co reussi" << std::endl;
      titi->set("titi");
      if(titi->save())
	std::cout << "update reussi" << std::endl;
    }
  else
    {
      std::cout << "CREATE" << std::endl;
      titi = new Account("titi", "toti", "kikoo", 0, _SQL);
      if(titi->save())
	std::cout << "compte cree" << std::endl;
      else
	std::cout << "Can't save the account" << std::endl;
    }
}

int	main()
{
  try
    {
      run();
    }
  catch (char const *e)
    {
      std::cout << e << std::endl;
      exit(0);
    }
}
