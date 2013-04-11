#ifndef SERVER_H_
#define SERVER_H_

//INCLUDE STLIB
#include <iostream>
#include <string>
#include <list>

//INCLUDE DE CLASSE PERSO
#include "Socket.hh"
#include "User.hh"
#include "GameServer.hh"
#include "Client.hh"
#include "SQLManager.hh"

//INCLUDE DE LIB
#include <msgpack.hpp>

//INCLUDE DE CLASSE SPECIFIQUE A MSGPACK
#include "../../MasterData/MasterData.hpp"
#include "../../MasterData/ServList.hpp"
#include "../../MasterData/Command.hpp"
#include "../../MasterData/Co.hpp"

//SOME DEFINE
#define EXIT_SUCCESS	0
#define EXIT_ERROR	-1
#define LISTEN_SIZE	5

class Server
{
 public:
  // FONCTION MOTRICE DU SERVEUR (Server_base.cpp)
  Server(int);
  ~Server();
  int	Initialisation(void);
  int	Run(void);
  void	AcceptCo();
  //  int	OdlerFd(void);

  // FONCTION DE RECEPTION (Server_manage.cpp)
  void	ManageUser();
  void	ManageGameServer();
  void	ManageUnknown();

  // FONCTION DE VERIFICATION D'IDENTITER (Server_login.cpp)
  void  CheckCoUser(Socket *, msgpack::sbuffer&);
  void  CheckRegUser(Socket *, msgpack::sbuffer&);
  void  AddServer(Socket *, msgpack::sbuffer&);

  // FONCTION UTILITAIRE (Serveur_utile.cpp)
  int	isCo(std::string);
  GameServer* getServById(int id);
  User* getPlayerByLog(std::string log);
  void	resetIG(GameServer *s);
  void	DelUser(User *);
  void	DelGameServer(GameServer *);

  // FONCTION POUR LES COMMANDE (Server_Command.cpp)
  void	SendServList(Socket *);
  void	sendCoSucces(User *);
  void	sendFailure(Socket *, std::string);
  void	BroadcastMsg(User *, msgpack::sbuffer&);
  void	JoinServer(User* u, msgpack::sbuffer&);
  void	EndGame(GameServer *s, msgpack::sbuffer &sbuf);

  // FONCTION POUR LES SUCCES (Server_succes.cpp)
  void	checkSucces(User *);
  void	checkSucces_1(User *);


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
