#include "./../include/Socket.hh"
#include "./../include/Client.hh"

Client::~Client()
{
  _soc = NULL;
}

Socket	*Client::getSocket()
{
  return _soc;
}


void	Client::setSocket(Socket* soc)
{
  _soc = soc;
}

