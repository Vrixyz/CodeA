#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

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
  User *p;
  
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
