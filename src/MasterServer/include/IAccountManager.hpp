//
// IDataManager.hpp for  in /home/berger_t/PFA/src/MasterServer/src
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Oct 23 14:13:05 2012 thierry berger
// Last update Tue Oct 23 15:05:06 2012 thierry berger
//

#ifndef IACCOUNT_MANAGER_HPP_
# define IACCOUNT_MANAGER_HPP_
#include "IAccount.hpp"

template<typename T>
class	IAccountManager
{
public:

  bool initialize() = 0; // true if succeed
  IAccount<T>* createAccount(const std::string& login, const std::string& passwd) = 0; // TODO: add mail
  bool deleteAccount(const IAccount<T>&) = 0;
  bool updateAccount(const IAccount<T>&) = 0;
  IAccount<T>* tryConnect(const std::string& login, const std::string& passwd) = 0;
protected:
  class IDataManager
  {
    bool initialize(IAccountManager&, Account& account) = 0;
    bool save(T data) = 0;
    T load() const = 0;
  };
  IDataManager& getDataManagerForAccount(const IAccount&) const = 0;
};

#endif
