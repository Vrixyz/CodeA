#include "./../include/User.hh"

User::User(std::string login)
{
  _login = login;
  _ig = false;
  games_win = 0;
  games_win_1 = 0;
  games_win_2 = 0;
  games_played = 0;
  games_played_1 = 0;
  games_played_2 = 0;
}

User::~User()
{
}
