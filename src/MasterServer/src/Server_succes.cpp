#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

void	Server::checkSucces(User *u)
{
  if(u->succes[0] != '1')
    checkSucces_1(u);
}

void	Server::checkSucces_1(User *u)
{
  if (u->games_win_1 >= 1)
    u->succes[0] = 1;
}


