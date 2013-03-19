#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

// CAN GO OUT
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
  std::cout << "LANCEMENT DU MASTER SUR LE PORT " << port << std::endl;
  server->Run();
  return EXIT_SUCCESS;
}

//BASE
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
  _sql->insertElem("toto42", "passw");
  return EXIT_SUCCESS;
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
      client->setNonBlock();
      client->setIP(_socket->getIP());
      std::cout << "SUCCESS: Nouvelle socket" << std::endl;
      _unknown.push_back(client);
    }
}

//MANAGE
void Server::ManageUser()
{
  std::string				message;
  std::list<User *>::iterator		it;
  unsigned int				i;
  int					cmd;

  for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
    if (FD_ISSET((*it)->getSoc()->getFD(), &_readfds))
      {
	msgpack::sbuffer sbuf;
	std::cout << "USER " << (*it)->getName() << std::endl;
	(*it)->getSoc()->RecvString(sbuf);
	
	msgpack::unpacker pac;
	pac.reserve_buffer(sbuf.size());
	memcpy(pac.buffer(), sbuf.data(), sbuf.size());
	pac.buffer_consumed(sbuf.size());
	msgpack::unpacked result;

	if (sbuf.size() == 0)
	  DelUser(*it);

	if (pac.next(&result)) 
	  {
	    int idCmd;
	    result.get().convert(&idCmd);
	    switch(idCmd)
	      {
	      case MasterData::Command::ASK_SERVER_LIST:
		SendServList((*it)->getSoc());
		break;
	      case MasterData::Command::SEND_CHAT:
		BroadcastMsg(*it, sbuf);
		break;
	      case MasterData::Command::REQUEST_SERVER:
		JoinServer(*it, sbuf);
		break;
	      default:
		std::cerr << "Command inconnu" << std::endl;
		break;
	      }
	  }
      }
}

void Server::ManageGameServer()
{
  std::list<GameServer *>::iterator		it;
  unsigned int					i;
  int						cmd;

  for (i = 0, it = _server.begin(); i < _server.size(); i++, it++)
    if (FD_ISSET((*it)->getSoc()->getFD(), &_readfds))
      {	
	msgpack::sbuffer sbuf;
	(*it)->getSoc()->RecvString(sbuf);

	if (sbuf.size() == 0)
	  {
	    DelGameServer(*it);
	    break;
	  }
	
	msgpack::unpacker pac;
	pac.reserve_buffer(sbuf.size());
	memcpy(pac.buffer(), sbuf.data(), sbuf.size());
	pac.buffer_consumed(sbuf.size());
	msgpack::unpacked result;
	
	if (pac.next(&result)) 
	  {
	    int idCmd;
	    result.get().convert(&idCmd);
	    switch(idCmd)
	      {
	      case MasterData::Command::ENDGAME:
		EndGame((*it), sbuf);
		break;
	      default:
		std::cerr << "Command inconnu" << std::endl;
		break;
	      }
	  }

      }
}

void Server::ManageUnknown()
{
  std::list<Socket *>::iterator		it;
  unsigned int				i;
  int					cmd;
  Socket*				client;

  for (i = 0, it = _unknown.begin(); i < _unknown.size(); i++, it++)
    if (FD_ISSET((*it)->getFD(), &_readfds))
      {	
	msgpack::sbuffer sbuf;
	(*it)->RecvString(sbuf);

	if (sbuf.size() == 0)
	  {
	    _unknown.remove(*it);
	    (*it)->Close();
	  }
	client = *it;

	msgpack::unpacker pac;
	pac.reserve_buffer(sbuf.size());
	memcpy(pac.buffer(), sbuf.data(), sbuf.size());
	pac.buffer_consumed(sbuf.size());
	msgpack::unpacked result;

	//CHECK DU TYPE DE CLIENT ET DE LA VALIDER DU LOGIN MDP
	if (pac.next(&result)) 
	  {
	    int idCmd;
	    result.get().convert(&idCmd);
	    switch(idCmd)
	      {
	      case MasterData::Command::REGISTER_USER:
		CheckRegUser(client, sbuf);
		break;
	      case MasterData::Command::CONNECT_USER:
		CheckCoUser(client, sbuf);
		break;
	      case MasterData::Command::CONNECT_SERVER:
		AddServer(client, sbuf);
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

//LOGIN
void	Server::CheckCoUser(Socket *soc, msgpack::sbuffer &sbuf)
{
  User*			u;
  MasterData::CoClient	co("", "");

  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;

  if (pac.next(&result)) 
    {
      if (pac.next(&result))
	{
	  result.get().convert(&co);
	  if(isCo(co.login))
	    {
	      sendFailure(soc, "Utilisateur deja loguer");
	      std::cout << "Compte deja loguer" << std::endl;
	    }
	  else if ((u = _sql->findUser(co.login, co.pass)) != NULL)
	    {	      
	      u->setSoc(soc);
	      _users.push_back(u);
	      _unknown.remove(soc);
	      std::cout << "SUCCES DE LA CONNEXION" << std::endl;
	      sendCoSucces(u);
	      return; 
	    }
	  else
	    sendFailure(soc, "Combinaison user/pass invalid");
	}
    }
  _unknown.remove(soc);
  soc->Close();
}

void	Server::CheckRegUser(Socket *soc, msgpack::sbuffer &sbuf)
{
  User*			u;
  MasterData::RegClient	reg("", "");

  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;

  if (pac.next(&result)) 
    {
      if (pac.next(&result))
	{
	  result.get().convert(&reg);
	  if (_sql->insertElem(reg.login, reg.pass) != -1)
	    {
	      u = new User(reg.login);	      
	      u->setSoc(soc);
	      _users.push_back(u);
	      _unknown.remove(soc);
	      std::cout << "SUCCES DE L'AJOUT D'un COMPTE" << std::endl;
	      sendCoSucces(u);
	      return; 
	    }
	  sendFailure(soc, "Impossible de creer un compte avec ce login/pass");
	}
    }
  _unknown.remove(soc);
  soc->Close();
}

void	Server::AddServer(Socket *soc, msgpack::sbuffer &sbuf)
{
  GameServer*		s;
  MasterData::CoServer	co(0, "");

  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;

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

//UTILE
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

//COMMAND
void Server::SendServList(Socket* soc)
{
  //SEGFAULT RANDOM ARRIVER 2 FOIS DANS CETTE FONCTION FAIRE DES TEST POUR LE TROUVER
  GameServer *					s;
  std::list<GameServer *>::iterator		it;
  unsigned int					i;

  std::cout << "Liste send" << std::endl;
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  packet.pack((int)MasterData::Command::SEND_SERVER_LIST);

  for (i = 0, it = _server.begin(); i < _server.size(); i++, it++)
    {
      s = *it;
      MasterData::Serv	serveur(s->getId(), s->getName());
      packet.pack(serveur);
    }
  soc->sendToServer(sbuf);
}

void	Server::sendCoSucces(User *u)
{
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  MasterData::InfosClient ic(u->getName());
  
  packet.pack((int)MasterData::Command::INFOS_CLIENT);
  packet.pack(ic);
  u->getSoc()->sendToServer(sbuf);
}

void	Server::sendFailure(Socket *soc, std::string msg)
{
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  MasterData::ErrorMsg err(msg);
  
  packet.pack((int)MasterData::Command::ERROR);
  packet.pack(err);
  soc->sendToServer(sbuf);
}

void Server::BroadcastMsg(User* u, msgpack::sbuffer &sbuf)
{
  MasterData::SendChat msg("");  
  std::list<User *>::iterator		it;
  unsigned int				i;

  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;

  if (pac.next(&result))
    {
      pac.next(&result);
      result.get().convert(&msg);
      msgpack::sbuffer buf;
      msgpack::packer<msgpack::sbuffer> packet(&buf);  
      packet.pack((int)MasterData::Command::RECV_CHAT);
      MasterData::RecvChat tosend(u->getName(), msg.msg);
      packet.pack(tosend);    

      for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
	{
	  if ((*it)->isInGame() == false)
	    (*it)->getSoc()->sendToServer(buf);
	}
    }    
}

void Server::JoinServer(User* u, msgpack::sbuffer &sbuf)
{
  std::list<User *>::iterator		it;
  unsigned int				i;
  GameServer *				s;
  
  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;
  
  if (pac.next(&result))
    {
      std::cout << "RECEPTION SERV" << std::endl;
      pac.next(&result);
      int idServ;
      result.get().convert(&idServ);
      s = getServById(idServ);
      if (s == NULL || s->getFree() <= 0)
	{
	  sendFailure(u->getSoc(), "Serveur introuvable ou complet");
	  return;
	}
      else
	{
	  std::cout << "ENVOI DE DATA DE CLIENT AU GAME SERVER" << std::endl; 

	  msgpack::sbuffer buf1;
	  msgpack::packer<msgpack::sbuffer> packet1(&buf1);
	  MasterData::InfosPlayer player(u->getSoc()->getIP(), u->getName());  
	  packet1.pack((int)MasterData::Command::PLAYER_JOIN);
	  packet1.pack(player);
	  std::cout << "taille envoyee : "<< s->getSoc()->sendToServer(buf1) << std::endl;
	  

	  std::cout << "ip : " << player.ip << ", name: " << player.name << std::endl;

	  std::cout << "ENVOI DE DATA DE CO AU CLIENT" << std::endl; 
	  msgpack::sbuffer buf2;
	  msgpack::packer<msgpack::sbuffer> packet2(&buf2);
	  MasterData::InfosServer serv(s->getSoc()->getIP(), s->getPort());  
	  packet2.pack((int)MasterData::Command::INFOS_SERVER);
	  packet2.pack(serv);
	  u->getSoc()->sendToServer(buf2);
	  u->setIG(true);
	  u->setServ(s);
	  s->addPlayer();
	}      
    }
}

void Server::EndGame(GameServer *s, msgpack::sbuffer &sbuf)
{
  msgpack::unpacker pac;
  pac.reserve_buffer(sbuf.size());
  memcpy(pac.buffer(), sbuf.data(), sbuf.size());
  pac.buffer_consumed(sbuf.size());
  msgpack::unpacked result;
  
  if (pac.next(&result)) 
    {
      while(pac.next(&result))
	{
	  MasterData::EndGame eg("", false, 0);
	  result.get().convert(&eg);	  
	  std::cout << "FIN DE GAME DE " << eg.login;
	  if (eg.win)
	    std::cout << " VICTOIRE";
	  else
	    std::cout << " DEFAITE";
	  std::cout << " EN TEMPS QUE " << eg.r << std::endl;
	}
    }
  s->resetPlayer();
  resetIG(s);
}
