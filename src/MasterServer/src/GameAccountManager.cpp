#include "GameAccountManager.hpp"

bool GameAccountManager::initialize()
{
  return true;
}

IAccount<std::string>* GameAccountManager::createAccount(const std::string& login,const std::string& pass)
{
  return NULL;
}

bool GameAccountManager::deleteAccount(const IAccount<std::string>& account)
{
  return true;
}

bool GameAccountManager::updateAccount(const IAccount<std::string>& account)
{
  return true;
}

IAccount<std::string>* GameAccountManager::tryConnect(const std::string&login, const std::string& pass)
{
  return NULL;
}

bool GameAccountManager::SQLDataManager::initialize(GameAccountManager& accountmanager, IAccount<std::string>& account)
{
  return true;
}

bool GameAccountManager::SQLDataManager::save(std::string data)
{
  return true;
}

std::string GameAccountManager::SQLDataManager::load() const
{
  return "";
}

// IDataManager* GameAccountManager::getDataManagerForAccount(const IAccount<std::string>&) const
// {
//   return NULL;
// }
