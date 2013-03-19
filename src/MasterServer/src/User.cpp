#include "./../include/User.hh"

User::User(std::string login)
{
  _login = login;
  _ig = false;
  _game = NULL;
}

User::~User()
{
}
