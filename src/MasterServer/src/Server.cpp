#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

int	main(int ac, char **av)
{
  int port = 4242;
  if (ac == 2)
    port = atoi(av[1]);
  Server * server = new Server(port);

  std::cout << "INITIALISATION" << std::endl;
  if (server->Initialisation() == EXIT_ERROR)
    return EXIT_FAILURE;
  std::cout << "SUCCES" << std::endl;
  std::cout << "LANCEMENT DU SERVEUR SUR LE PORT " << 4242 << std::endl;
  server->Run();
  return EXIT_SUCCESS;
}

Server::Server(int port)
{
  _idmax = 0;
  _port = port;
  _socket = new Socket();
  _sql = new SQLManager();
}

int	Server::Initialisation(void)
{
  if (_socket->init() == -1)
    {
      std::cerr << "une erreur s'est produite lors de la commande system socket UNIX" << std::endl;
      return EXIT_ERROR;
    }

  _sin.sin_family = AF_INET;
  _sin.sin_port = htons(_port);
  _sin.sin_addr.s_addr = INADDR_ANY;

  if (_socket->Bind(_sin) == -1)
    {
      _socket->Close();
      std::cerr << "une erreur s'est produite lors de la commande system bind UNIX" << std::endl;
      return EXIT_ERROR;
    }
  if (_socket->Listen(LISTEN_SIZE) == -1)
    {
      _socket->Close();
      std::cerr << "une erreur s'est produite lors de la commande system listen UNIX" << std::endl;
      return EXIT_ERROR;
    }
  if (_sql->coDB() == -1)
    {
      _socket->Close();
      return EXIT_ERROR;
    }
  _sql->createUsersTable();
  //  _sql->insertElem("toto42", "passw");
  return EXIT_SUCCESS;
}

void    Server::AcceptCo()
{
  std::string	message;
  Socket*	client;
  int		soc;

  soc = _socket->Accept(_sin_client, sizeof(_sin_client));
  if (soc == -1)
    {
      std::cerr << "une erreur est survenue lors de la commande system accept" << std::endl;
      _socket->Close();
    }
  else
    {
      //CREATION DE LA SOCKET
      client  = new Socket();
      client->setFD(soc);
      std::cout << "SUCCESS: Connexion d'un client" << std::endl;
      _unknown.push_back(client);
    }
}

int	Server::Run(void)
{
  std::list<User *>::const_iterator		Uit;
  std::list<Socket *>::const_iterator		UKit;
  std::list<GameServer *>::const_iterator	Sit;
  unsigned int					i;
  int						maxFD;

  while (1)
    {
      FD_ZERO(&(_readfds));
      maxFD = _socket->getFD();

      FD_SET(_socket->getFD(), &_readfds);

      //UNKNOW FD
      for (i = 0, UKit = _unknown.begin(); i < _unknown.size() ; UKit++, i++)
	{
	  FD_SET((*UKit)->getFD(), &_readfds);
	  if ((*UKit)->getFD() > maxFD)
	    maxFD = (*UKit)->getFD();
	}

      //USER FD    
      for (i = 0, Uit = _users.begin(); i < _users.size() ; Uit++, i++)
	{
	  FD_SET((*Uit)->getSoc()->getFD(), &_readfds);
	  if ((*Uit)->getSoc()->getFD() > maxFD)
	    maxFD = (*Uit)->getSoc()->getFD();
	}
      
      //SERVER FD      
      for (i = 0, Sit = _server.begin(); i < _server.size() ; Sit++, i++)
	{
	  FD_SET((*Sit)->getSoc()->getFD(), &_readfds);
	  if ((*Sit)->getSoc()->getFD() > maxFD)
	    maxFD = (*Sit)->getSoc()->getFD();
	}


      //SELECT VEUT MAXFD +1
      maxFD++;

      
      if ((_socket->Select(maxFD, &_readfds) == -1))
	{
	  std::cerr << "une erreur est survenue lors de la commande system select UNIX" << std::endl;
	  return EXIT_ERROR;
	}
      if (FD_ISSET(_socket->getFD(), &_readfds))
	  AcceptCo();

      //USER MESSAGE
      ManageUser();

      // SERVEUR MESSAGE
      ManageGameServer();

      //UNKWON MESSAGE
      ManageUnknown();
    }
  return EXIT_SUCCESS;
}


void Server::ManageUser()
{
  std::string				message;
  std::list<User *>::iterator		it;
  unsigned int				i;
  int					cmd;

  for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
    if (FD_ISSET((*it)->getSoc()->getFD(), &_readfds))
      {	
	(*it)->getSoc()->RecvString(message);
	std::cout << "USER " << message << std::endl;
	if (message.length() == 0)
	  DelUser(*it);

	msgpack::unpacker pac;
	pac.reserve_buffer(message.length());
	memcpy(pac.buffer(), message.data(), message.length());
	pac.buffer_consumed(message.length());
	msgpack::unpacked result;
	if (pac.next(&result)) 
	  {
	    int idCmd;
	    result.get().convert(&idCmd);
	    switch(idCmd)
	      {
	      case MasterData::Command::ASK_SERVER_LIST:
		SendServList((*it)->getSoc());
		break;
	      default:
		std::cerr << "Command inconnu" << std::endl;
		break;
	      }
	  }
      }
}

void Server::SendServList(Socket* soc)
{
  GameServer *					s;
  std::list<GameServer *>::iterator		it;
  unsigned int					i;
  std::list<MasterData::Serv>			slist;
  MasterData::Serv				serveur;
  MasterData::ListServ				sl;

  for (i = 0, it = _server.begin(); i < _server.size(); i++, it++)
    {
      s = *it;
      serveur.id = s->getId();
      serveur. name = s->getName();
      slist.push_back(serveur);
    }
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  packet.pack((int)MasterData::Command::SEND_SERVER_LIST);
  sl.list = slist;
  packet.pack(sl);
  soc->sendToServer(sbuf);
}

void Server::ManageGameServer()
{
  std::string					message;
  std::list<GameServer *>::iterator			it;
  unsigned int					i;
  int						cmd;

  for (i = 0, it = _server.begin(); i < _server.size(); i++, it++)
    if (FD_ISSET((*it)->getSoc()->getFD(), &_readfds))
      {	
	(*it)->getSoc()->RecvString(message);
	std::cout << "SERVER " << message << std::endl;
	if (message.length() == 0)
	  DelGameServer(*it);
      }
}


void Server::ManageUnknown()
{
  std::string				message;
  std::list<Socket *>::iterator		it;
  unsigned int				i;
  int					cmd;
  Socket*				client;

  for (i = 0, it = _unknown.begin(); i < _unknown.size(); i++, it++)
    if (FD_ISSET((*it)->getFD(), &_readfds))
      {	
	(*it)->RecvString(message);
	if (message.length() == 0)
	  {
	    _unknown.remove(*it);
	    (*it)->Close();
	  }

	client = *it;

	//CHECK DU TYPE DE CLIENT ET DE LA VALIDER DU LOGIN MDP
	msgpack::unpacker pac;
	pac.reserve_buffer(message.length());
	memcpy(pac.buffer(), message.data(), message.length());
	pac.buffer_consumed(message.length());
	msgpack::unpacked result;
	if (pac.next(&result)) 
	  {
	    int idCmd;
	    result.get().convert(&idCmd);
	    switch(idCmd)
	      {
	      case MasterData::Command::CONNECT_USER:
		CheckCoUser(client, message);
		break;
	      case MasterData::Command::CONNECT_SERVER:
		AddServer(client, message);
		break;
	      default:
		std::cerr << "ERROR: client non conforme deconnexion du client" << std::endl;
		_unknown.remove(client);
		client->Close();
		break;
	      }
	  }
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

void	Server::AddServer(Socket *soc, std::string infos)
{
  GameServer*		s;
  msgpack::unpacker	pac;
  msgpack::unpacked	result;
  MasterData::CoServer	co(0, "");

  pac.reserve_buffer(infos.length());
  memcpy(pac.buffer(), infos.data(), infos.length());
  pac.buffer_consumed(infos.length());
  if (pac.next(&result)) 
    {
      if (pac.next(&result))
	{
	  result.get().convert(&co);
	  s = new GameServer(co.port, co.name, _idmax++);
	  s->setSoc(soc);
	  _server.push_back(s);
	  _unknown.remove(soc);
	  std::cout << "SUCCES DE L'AJOUT D'UN SERVER" << std::endl;
	  return; 
	}
    }
  _unknown.remove(soc);
  soc->Close();
}


void	Server::CheckCoUser(Socket *soc, std::string infos)
{
  User*			u;
  msgpack::unpacker	pac;
  msgpack::unpacked	result;
  MasterData::CoClient	co("", "");

  pac.reserve_buffer(infos.length());
  memcpy(pac.buffer(), infos.data(), infos.length());
  pac.buffer_consumed(infos.length());
  if (pac.next(&result)) 
    {
      if (pac.next(&result))
	{
	  result.get().convert(&co);
	  if ((u = _sql->findUser(co.login, co.pass)) != NULL)
	    {	      
	      u->setSoc(soc);
	      _users.push_back(u);
	      _unknown.remove(soc);
	      std::cout << "SUCCES DE LA CONNEXION" << std::endl;
	      sendCoSucces(u);
	      return; 
	    }
	  sendFailure(soc, "Combinaison user/pass invalid");
	}
    }
  _unknown.remove(soc);
  soc->Close();
}

void	Server::sendCoSucces(User *u)
{
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  packet.pack((int)MasterData::Command::INFOS_CLIENT);
  MasterData::InfosClient ic(u->getName());
  packet.pack(ic);
  u->getSoc()->sendToServer(sbuf);
}

void	Server::sendFailure(Socket *soc, std::string msg)
{
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  packet.pack((int)MasterData::Command::ERROR);
  MasterData::ErrorMsg err(msg);
  packet.pack(err);
  soc->sendToServer(sbuf);
}
