//
// IAccount.hpp for  in /home/berger_t/PFA/src/MasterServer/src
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Tue Oct 23 14:43:29 2012 thierry berger
// Last update Tue Oct 23 15:05:03 2012 thierry berger
//

#ifndef IACCOUNT_HPP_
# define IACCOUNT_HPP_

template<typename T>
class	IAccount
{
public:
  int getId() const = 0;
  const std::string& getLogin() const = 0;
  void setLogin(const std::string&) = 0;
  const std::string& getPasswd() const = 0;
  void setPasswd(const std::string&) = 0;
  const std::string& getMailAddress() const = 0;
  void setMailAddress(const std::string&) = 0;
  /// data would be specific game/program data (successes/account statistics in our game)
  const T& getData() const = 0;
  /// T would inherit from a ISerializable adapted to the DataManager
  void setData(const T&) = 0;
};

#endif
