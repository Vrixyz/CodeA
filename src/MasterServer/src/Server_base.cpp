#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

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
