#include "./../include/User.hh"

User::User(std::string login)
{
  _login = login;
  _ig = false;
  _game = NULL;
  games_win = 0;
  games_win_1 = 0;
  games_win_2 = 0;
  games_played = 0;
  games_played_1 = 0;
  games_played_2 = 0;
  succes = "";
}

User::~User()
{
}

void		addStat(User* u, MasterData::EndGame eg)
{
  u->games_played += 1;
  if (eg.win)
    u->games_win += 1;
  if(eg.r == GameData::CommandStruct::BePlayer::INVOKER)
    {
      u->games_played_1 += 1;
      if (eg.win)
	u->games_win_1 += 1;
    }
  else
    {
      u->games_played_2 += 1;
      if (eg.win)
	u->games_win_2 += 1;
    }
}
