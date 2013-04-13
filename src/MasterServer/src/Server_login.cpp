#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

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
	      sendSucces(u);
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
	  SendServToAll();
	  return; 
	}
    }
  _unknown.remove(soc);
  soc->Close();
}
