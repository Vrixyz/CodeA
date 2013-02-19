#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <string>
#include <list>

#include "Socket.hh"
#include <msgpack.hpp>
#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1
#define LISTEN_SIZE	5

class Server
{
 public:

  Server(int, std::string, int);
  ~Server();

  int	Initialisation(void);
  int	Run(void);
  void	AcceptCo();
  void	ManageUnknown();
  int	OdlerFd(void);

 protected:
  std::list<Socket *>	_unknown;
  Socket *		_socket;
  Socket *		_master;
  int			_port;
  std::string		_ipM;
  int			_portM;
  fd_set		_readfds;
  fd_set		_writefds;

  struct sockaddr_in	_sin;
  struct sockaddr_in	_sin_client;
};

#endif
