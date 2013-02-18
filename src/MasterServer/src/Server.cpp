#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

int	main(int ac, char **av)
{
  (void)ac;
  (void)av;
  Server * server = new Server(atoi(av[1]));

  if (server->Initialisation() == EXIT_ERROR)
    return EXIT_FAILURE;
  server->Run();
  return EXIT_SUCCESS;
}

Server::Server(int port)
{
  _port = port;
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

  return EXIT_SUCCESS;
}

int	Server::Run(void)
{
  std::list<Socket *>::const_iterator	it;
  unsigned int				i;
  int					soc;

  Client*	toAdd;
  Socket*	client;

  while (1)
    {
      FD_ZERO(&(_readfds));
      
      for (i = 0, it = _client.begin(); i < _client.size() ; it++, i++)
	FD_SET((*it)->getFD(), &_readfds);

      //      for (i = 0, it = _client.begin(); i < _client.size() ; it++, i++)
      //FD_SET((*it)->getSocket()->getFD(), &_readfds);

      FD_SET(_socket->getFD(), &_readfds);

      
      if ((_socket->Select(_client, &_readfds) == -1))
	{
	  std::cerr << "une erreur est survenue lors de la commande system select UNIX" << std::endl;
	  return EXIT_ERROR;
	}

      if (FD_ISSET(_socket->getFD(), &_readfds))
	{
	  soc = _socket->Accept(_sin_client, sizeof(_sin_client));
	  if (soc == -1)
	    {
	      std::cerr << "une erreur est survenue lors de la commande system accept" << std::endl;
	      _socket->Close();
	    }
	  else
	    {
	      std::string cmd;
	      client  = new Socket();
	      client->setFD(soc);
	      std::cout << "SUCCESS: Connexion d'un client" << std::endl;
	      AddClient(client);
	    }
	}
      this->ManageClient();
      //      this->ManageClient();
    }
  return EXIT_SUCCESS;
}

void Server::ManageClient()
{
  std::list<Socket *>::iterator		it;
  std::string				message;
  unsigned int				i;
  int					cmd;

  for (i = 0, it = _client.begin(); i < _client.size(); i++, it++)
    if (FD_ISSET((*it)->getFD(), &_readfds))
      {	
	(*it)->RecvString(message);
	if (message.length() == 0)
	  DelClient(*it);
	
	msgpack::unpacker pac;
        pac.reserve_buffer(message.length());
        memcpy(pac.buffer(), message.data(), message.length());
        pac.buffer_consumed(message.length());
	msgpack::unpacked result;
        if (pac.next(&result)) {
	  int idCmd;
	  result.get().convert(&idCmd);
	  if ((idCmd == MasterData::Command::CONNECT_CLIENT))
	    {
	      MasterData::CoClient co("", "");
	      pac.next(&result); // get the playerDefinition
	      result.get().convert(&co);
	      
	      
	      //std::cout << co.login << std::endl;
	      //std::cout << co.pass << std::endl; 
	    }	
	}
      }
}

void	Server::AddClient(Socket *client)
{
  _client.push_back(client);
}

void	Server::DelClient(Socket *client)
{
  _client.remove(client);
}

std::list<Socket *>	Server::getClient()
{
  return _client;
}

