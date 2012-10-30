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
  virtual bool reset() = 0; // true if succeed  
  // le create account n'envoi pas le mail de confirmation
  virtual IAccount<T>* createAccount(const std::string& login, const std::string& passwd, const std::string& mail) = 0;
  virtual bool deleteAccount(const IAccount<T>&) = 0;
  virtual bool updateAccount(const IAccount<T>&) = 0;
  virtual IAccount<T>* tryConnect(const std::string& login, const std::string& passwd) = 0;
  virtual IAccount<T>* getAccountById(int id) = 0;
  //  virtual bool setPasswd(const std::string oldpass&, const std::string newpass&, IAccount<T>&) = 0;
};

#endif
