#include "GameAccount.hpp"

int GameAccount::getId() const
{
  return _id;
}

const std::string& GameAccount::getLogin() const
{
  return _login;
}

void GameAccount::setLogin(const std::string& login)
{
  _login = login;
}

const std::string& GameAccount::getPasswd() const
{
  return _pass;
}

void GameAccount::setPasswd(const std::string& pass)
{
  _pass = pass;
}

const std::string& GameAccount::getMailAddress() const
{
  return _mail;
}

void GameAccount::setMailAddress(const std::string& mail)
{
  _mail = mail;
}

const std::string& GameAccount::getData() const
{
  return _data;
}

void GameAccount::setData(const std::string& data)
{
  _data = data;
}

