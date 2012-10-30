#ifndef GAMEACCOUNT_HPP_
# define GAMEACCOUNT_HPP_

#include "IAccount.hpp"

class GameAccount : public IAccount<std::string>
{
private:
  int		_id;
  std::string	_login;
  std::string	_pass;
  std::string	_mail;
  std::string	_data;
public:
  int getId() const;
  void setId(int);
  const std::string& getLogin() const;
  void setLogin(const std::string&);
  const std::string& getPasswd() const;
  void setPasswd(const std::string&);
  const std::string& getMailAddress() const;
  void setMailAddress(const std::string&);
  const std::string& getData() const;
  void setData(const std::string&);
};

#endif
