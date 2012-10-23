//
// IDataManager.hpp for  in /home/berger_t/PFA/src/MasterServer/src
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Oct 23 14:13:05 2012 thierry berger
// Last update Tue Oct 23 15:05:06 2012 thierry berger
//

#ifndef IDATA_MANAGER_HPP_
# define IDATA_MANAGER_HPP_

class	IDataManager
{
public:
  bool initialize() = 0; // true if succeed
  Account* createAccount(const std::string& login, const std::string& passwd) = 0; // TODO: add mail
  bool deleteAccount(const Account&) = 0;
  
  bool updateAccount(const Account&) = 0;
  Account* tryConnect(const std::string& login, const std::string& passwd) = 0;
};

#endif
