#ifndef GAMEACCOUNT_MANAGER_HPP_
# define GAMEACCOUNT_MANAGER_HPP_

#include "IAccountManager.hpp"
#include "GameAccount.hpp"

class GameAccountManager : public IAccountManager<std::string>
{
private:

public:
  bool initialize();
  IAccount<std::string>* createAccount(const std::string& login, const std::string& passwd);
  bool deleteAccount(const IAccount<std::string>&);
  bool updateAccount(const IAccount<std::string>&);
  IAccount<std::string>* tryConnect(const std::string& login, const std::string& pass);
protected:
  class SQLDataManager
  {
    bool initialize(GameAccountManager&, IAccount<std::string>&);
    bool save(std::string data);
    std::string load() const;
  };
  IDataManager* getDataManagerForAccount(const IAccount<std::string>&) const{};
};

#endif
