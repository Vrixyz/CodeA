#include "Define.hh"
#include "Server.hh"

int	main(int ac, char **av)
{
  if (ac == 4)
    {
      Server * server = new Server(atoi(av[1]), av[2], atoi(av[3]));

      std::cout << "INITIALISATION" << std::endl;
      if (server->Initialisation() == EXIT_ERROR)
	return EXIT_FAILURE;
      std::cout << "SUCCES" << std::endl;
      std::cout << "LANCEMENT DU SERVEUR SUR LE PORT " << atoi(av[1]) << std::endl;
      server->Run();
      return EXIT_SUCCESS;
    }
  else
    std::cerr << "Usage: ./Server port ipMaster portMaster" << std::endl;
  return EXIT_FAILURE;
}

Server::Server(int port, std::string ipM, int portM)
{
  _port = port;
  _ipM = ipM;
  _portM = portM;
  _socket = new Socket();
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
    
  _master = new Socket();
  if (_master->Connect(_ipM, _portM) == -1)
    {
      _socket->Close();
      _master->Close();
      std::cerr << "une erreur s'est produite lors de la co" << std::endl;
      return EXIT_ERROR;
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
      std::cout << "SUCCESS: Connexion d'un client" << std::endl;
      _unknown.push_back(client);
    }
}

int	Server::Run(void)
{
  std::list<Socket *>::const_iterator	UKit;
  unsigned int				i;
  int					maxFD;

  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  
  packet.pack((int)MasterData::Command::CONNECT_SERVER);
  MasterData::CoServer serv(_port, "No name on:" + _port);
  packet.pack(serv);
  _master->sendToServer(sbuf);

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

      //SELECT VEUT MAXFD +1
      maxFD++;

      
      if ((_socket->Select(maxFD, &_readfds) == -1))
	{
	  std::cerr << "une erreur est survenue lors de la commande system select UNIX" << std::endl;
	  return EXIT_ERROR;
	}
      if (FD_ISSET(_socket->getFD(), &_readfds))
	  AcceptCo();
      ManageUnknown();
    }
  return EXIT_SUCCESS;
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
