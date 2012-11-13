//
// CommandManager.hpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Thu Nov  8 13:13:44 2012 mathieu leurquin
// Last update Fri Nov  9 11:24:21 2012 mathieu leurquin
//

#ifndef COMMAND_MANAGER_HPP
# define COMMAND_MANAGER_HPP

#include <boost/thread.hpp>

#include <boost/array.hpp>

#include <msgpack.hpp>


namespace Server
{
  // C is the type of the (C)aller onto the callback will be called.
  // IdCom is the identity type of a command, must be msgpack packable.
  // IdClient is the identity type of a client, sent then to the Caller (not implemented)
  template<typename C, typename IdCom, typename IdClient>
  class CommandManager
  {
  public:
    CommandManager(C *c);
    // returns false in case of idCommand already handled. In this case, call removeCallBack first.
    bool addCallback(IdCom commandId, void (C::*methodToCall)(IdClient, char*));
    void removeCallback(IdCom commandId);

    // called by Communication
    void addCommandToQueue(IdClient sender, char* cmd); // msgpack::sbuffer ou equivalent (suite du packet envoye apres l'id de la commande
    
    // will call adequate caller functions to prepare the next update (function pointer)
    // then will delete handled commands
    void interpretCommands();
  private:
    C *caller;
    mutable boost::mutex _m_cmds;
    mutable boost::mutex _m_fcts;
    std::map<IdCom, void (C::*)(IdClient, char*)> fcts;
    std::vector<std::pair<char*, IdClient> >cmds;
  };
}

template<typename C, typename IdCom, typename IdClient>
Server::CommandManager<C, IdCom, IdClient>::CommandManager(C *c)
{
  caller = c;
}

template<typename C, typename IdCom, typename IdClient>
bool Server::CommandManager<C, IdCom, IdClient>::addCallback(IdCom commandId, void (C::*methodToCall)(IdClient, char*))
{
  boost::lock_guard<boost::mutex> lock(_m_fcts);

  if (fcts[commandId] == NULL)
    fcts[commandId] = methodToCall;
  else
    return false;
  return true;
}

template<typename C, typename IdCom, typename IdClient>
void Server::CommandManager<C, IdCom, IdClient>::removeCallback(IdCom commandId)
{
  boost::lock_guard<boost::mutex> lock(_m_fcts);

  fcts.erase(commandId);
}
      
// TODO: addCommandToSend, and interpretCommandToSend, this would become addCommandReceived
template<typename C, typename IdCom, typename IdClient>
void	Server::CommandManager<C, IdCom, IdClient>::addCommandToQueue(IdClient sender, char* cmd)
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  cmds.push_back(std::pair<char*, IdClient>(cmd, sender));
}

template<typename C, typename IdCom, typename IdClient>
void	Server::CommandManager<C, IdCom, IdClient>::interpretCommands()
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  for (unsigned int i = 0; i < cmds.size(); i++)
    {
      IdCom id;
      int size = sizeof(IdCom);
      msgpack::unpacker pac;
      msgpack::unpacked result;
      
      pac.reserve_buffer(size);
      memcpy(pac.buffer(), cmds[i].first, size);
      pac.buffer_consumed(size);
      if (pac.next(&result))
	{
	  msgpack::object obj = result.get();
	  obj.convert(&id);
	}
      (caller->*fcts[(IdCom)id])(cmds[i].second, cmds[i].first);
    }
  while (cmds.size() > 0)
    {
      cmds.pop_back();
    }
}

#endif
