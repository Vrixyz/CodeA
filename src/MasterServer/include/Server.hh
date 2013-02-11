#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <string>
#include <list>

#include "Socket.hh"
#include "Client.hh"

#define EXIT_SUCCESS 0
#define EXIT_ERROR -1
#define LISTEN_SIZE	5

class Server
{
 public:

  Server(int);
  ~Server();

  int	Initialisation(void);
  int	Run(void);
  void	AddClient(Client *);
  void	DelClient(Client *);
  void	ManageClient();
  int	OdlerFd(void);
  std::list<Client *>	getClient();

 protected:
  //ASocket *		_socClient;
  std::list<Client *>	_client;
  Socket *		_socket;
  int			_port;
  fd_set		_readfds;
  fd_set		_writefds;

  struct sockaddr_in	_sin;
  struct sockaddr_in	_sin_client;
};

#endif
