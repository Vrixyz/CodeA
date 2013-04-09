#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

int	Server::isCo(std::string login)
{
  std::list<User *>::iterator		it;
  unsigned int				i;

  for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
    {
      if((*it)->getName() == login)
	return 1;
    }
  return 0;
}

GameServer* Server::getServById(int id)
{
  std::list<GameServer *>::iterator		it;
  unsigned int					i;
  int						cmd;

  for (i = 0, it = _server.begin(); i < _server.size(); i++, it++)
    if ((*it)->getId() == id)
      return *it;
  return NULL;
}

void Server::resetIG(GameServer *s)
{
  std::list<User *>::iterator		it;
  unsigned int				i;
  
  for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
    if ((*it)->getServ() == s)
      {
	(*it)->setIG(false);
	(*it)->setServ(NULL);
      }
}

void	Server::DelUser(User *u)
{
  _users.remove(u);
}

void	Server::DelGameServer(GameServer *s)
{
  _server.remove(s);
}
