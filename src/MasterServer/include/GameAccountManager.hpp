#ifndef GAMEACCOUNT_MANAGER_HPP_
# define GAMEACCOUNT_MANAGER_HPP_

#include "IAccountManager.hpp"
#include "GameAccount.hpp"
#include <iostream>
#include "sqlite3.h"

class GameAccountManager : public IAccountManager<std::string>
{
private:
  std::string _dbname;
  sqlite3 *_db;
  //  bool _valid;
protected:
  IAccount<std::string>* getId(const std::string& login, IAccount<std::string>*);
public:
  GameAccountManager();
  bool reset();
  IAccount<std::string>* createAccount(const std::string& login, const std::string& passwd, const std::string& mail);
  bool deleteAccount(const IAccount<std::string>&);
  bool updateAccount(const IAccount<std::string>&);
  IAccount<std::string>* tryConnect(const std::string& login, const std::string& pass);
  IAccount<std::string>* getAccountById(int id);
  //  bool setPasswd(const std::string oldpass&, const std::string newpass&, IAccount<std::string>&);
};

#endif
