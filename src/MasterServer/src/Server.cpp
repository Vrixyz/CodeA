#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;
  Server * server = new Server(atoi(av[1]));

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
  std::list<User *>::const_iterator	Uit;
  std::list<Socket *>::const_iterator	UKit;
  //std::list<Socket *>::const_iterator	Sit;
  unsigned int				i;
  int					maxFD;

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
      //      ManageGameServer();

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
	if (message.length() == 0)
	  DelUser(*it);
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
	      return; 
	    }
	}
    }
  _unknown.remove(soc);
  soc->Close();
}
