#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

void Server::SendServToAll()
{
  std::list<User *>::iterator		it;
  unsigned int				i;

  for (i = 0, it = _users.begin(); i < _users.size(); i++, it++)
    {
      if ((*it)->isInGame() == false)
	SendServList((*it)->getSoc());
    }
}

void Server::SendServList(Socket* soc)
{
  std::cout << "CMD: LIST SERV SEND" << std::endl;
  GameServer *					s;
  std::list<GameServer *>::iterator		it;
  unsigned int					i;

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
  std::cout << "CMD: CO SUCCES" << std::endl;
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  MasterData::InfosClient ic(u->getName());
  
  packet.pack((int)MasterData::Command::INFOS_CLIENT);
  packet.pack(ic);
  u->getSoc()->sendToServer(sbuf);
}

void	Server::sendSucces(User *u)
{
  std::cout << "CMD: SEND SUCCES" << std::endl;
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  MasterData::RecvSucces  recv(u->succes);
  
  packet.pack((int)MasterData::Command::SUCCES);
  packet.pack(recv);
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

  std::cout << "CMD: SEND FAILURE" << std::endl;
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
  std::cout << "CMD: BROADCAST" << std::endl;
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
	  msgpack::sbuffer buf1;
	  msgpack::packer<msgpack::sbuffer> packet1(&buf1);
	  MasterData::InfosPlayer player(u->getSoc()->getIP(), u->getName());  
	  packet1.pack((int)MasterData::Command::PLAYER_JOIN);
	  packet1.pack(player);

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
  User *p;

  std::cout << "END" << std::endl;  
  if (pac.next(&result)) 
    {
      while(pac.next(&result))
	{
	  MasterData::EndGame eg("", false, 0);
	  result.get().convert(&eg);
	  std::cout << "FIN DE GAME DE " << eg.login;
	  p = getPlayerByLog(eg.login);
	  if (p != NULL)
	    {
	      addStat(p, eg);
	      checkSucces(p);
	      //PASTE SQL UPDATE HER

	      sendSucces(p);
	    }
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
