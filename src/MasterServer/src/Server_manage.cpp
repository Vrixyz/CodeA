#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

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
	std::cout << "GET A MESSAGE?" << std::endl;
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
	    std::cout << idCmd << "|" << MasterData::Command::END_GAME_SERV << std::endl; 
	    switch(idCmd)
	      {
	      case MasterData::Command::END_GAME_SERV:
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
