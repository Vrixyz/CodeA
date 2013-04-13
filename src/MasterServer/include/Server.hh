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
  void	SendServToAll();
  void	SendServList(Socket *);
  void	sendCoSucces(User *);
  void	sendSucces(User *);
  void	sendFailure(Socket *, std::string);
  void	BroadcastMsg(User *, msgpack::sbuffer&);
  void	JoinServer(User* u, msgpack::sbuffer&);
  void	EndGame(GameServer *s, msgpack::sbuffer &sbuf);

  // FONCTION POUR LES SUCCES (Server_succes.cpp)
  void	checkSucces(User *);
  void	checkSucces_1(User *);
  void  checkSucces_2(User *);
  void  checkSucces_3(User *);
  void  checkSucces_4(User *);
  void  checkSucces_5(User *);
  void  checkSucces_6(User *);
  void  checkSucces_7(User *);
  void  checkSucces_8(User *);
  void  checkSucces_9(User *);
  void  checkSucces_10(User *);
  void  checkSucces_11(User *);
  void  checkSucces_12(User *);
  void  checkSucces_13(User *);
  void  checkSucces_14(User *);
  void  checkSucces_15(User *);
  void  checkSucces_16(User *);
  void  checkSucces_17(User *);
  void  checkSucces_18(User *);
  void  checkSucces_19(User *);
  void  checkSucces_20(User *);
  void  checkSucces_21(User *);
  void  checkSucces_22(User *);
  void  checkSucces_23(User *);
  void  checkSucces_24(User *);
  void  checkSucces_25(User *);
  void  checkSucces_26(User *);
  void  checkSucces_27(User *);
  void  checkSucces_28(User *);
  void  checkSucces_29(User *);
  void  checkSucces_30(User *);
  void  checkSucces_31(User *);
  void  checkSucces_32(User *);
  void  checkSucces_33(User *);
  void  checkSucces_34(User *);
  void  checkSucces_35(User *);
  void  checkSucces_36(User *);
  void  checkSucces_37(User *);
  void  checkSucces_38(User *);
  void  checkSucces_39(User *);
  void  checkSucces_40(User *);
  void  checkSucces_41(User *);
  void  checkSucces_42(User *);
  void  checkSucces_43(User *);
  void  checkSucces_44(User *);
  void  checkSucces_45(User *);

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
