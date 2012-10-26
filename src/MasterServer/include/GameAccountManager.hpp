#ifndef GAMEACCOUNT_MANAGER_HPP_
# define GAMEACCOUNT_MANAGER_HPP_

#include "IAccountManager.hpp"
#include "GameAccount.hpp"

class GameAccountManager : public IAccountManager<std::string>
{
private:

public:
  bool initialize();
  GameAccount createAccount(const std::string& login, const std::string& passwd);
  bool deleteAccount(const GameAccount&);
  bool updateAccount(const GameAccount&);
  GameAccount tryConnect(const std::string& login, const std::string& pass);
protected:
  class SQLDataManager
  {
    bool initialize(GameAccountManager&, GameAccount&);
    bool save(std::string data);
    std::string load() const;
  };
  SQLDataManager& getDataManagerForAccount(const GameAccount&) const;
};

#endif
