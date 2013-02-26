#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <string>
#include <list>

#include "Socket.hh"
#include "User.hh"
#include "GameServer.hh"
#include "Client.hh"
#include "SQLManager.hh"
#include <msgpack.hpp>
#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/ServList.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

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
  void  CheckCoUser(Socket *, msgpack::sbuffer&);
  void  CheckRegUser(Socket *, msgpack::sbuffer&);
  void  AddServer(Socket *, msgpack::sbuffer&);
  void	SendServList(Socket *);
  void	AcceptCo();
  void	DelUser(User *);
  void	DelGameServer(GameServer *);
  void	ManageUser();
  void	ManageGameServer();
  void	ManageUnknown();
  int	OdlerFd(void);
  void	sendCoSucces(User *);
  void	sendFailure(Socket *, std::string);
  void	BroadcastMsg(User *, msgpack::sbuffer&);
  GameServer* getServById(int id);
  void	JoinServer(User* u, msgpack::sbuffer&);

 protected:
  SQLManager*			_sql;
  std::list<User *>		_users;
  std::list<GameServer *>	_server;
  std::list<Socket *>		_unknown;
  Socket *			_socket;
  int				_port;
  int				_idmax;
  fd_set			_readfds;
  fd_set			_writefds;

  struct sockaddr_in		_sin;
  struct sockaddr_in		_sin_client;
};

#endif
