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
#include <stdio.h>

namespace Server
{
  // C is the type of the (C)aller onto the callback will be called.
  // IdCom is the identity type of a command, must be msgpack packable.
  // IdClient is the identity type of a client, sent then to the Caller (not implemented)
  template<typename C, typename IdCom, typename IdClient>
  class CommandManager
  {
  public:
    class	ICallback
    {
    public:
      virtual void call(C* caller, IdClient, msgpack::sbuffer* data) const = 0;
    };

    CommandManager(C *c);
    // returns false in case of idCommand already handled. In this case, call removeCallBack first.
    bool addCallback(IdCom commandId, ICallback* callback);
    void removeCallback(IdCom commandId);

    // called by Communication
    void addCommandToQueue(IdClient sender, char* cmd, int size); // data d'un msgpack::sbuffer (suite du packet envoye apres l'id de la commande
    
    // will call adequate caller functions to prepare the next update (function pointer)
    // then will delete handled commands
    void interpretCommands();

    template<typename ArgType>
    ICallback* createCallback(void (C::*methodToCall)(IdClient, ArgType)) const
    {
      return new Callback<ArgType>(methodToCall);
    }

    ICallback* createCallback(void (C::*methodToCall)(IdClient)) const
    {
      return new CallbackNoArg(methodToCall);
    }


  private:
    C *caller;
    mutable boost::mutex _m_cmds;
    mutable boost::mutex _m_fcts;
    std::map<IdCom, ICallback*> fcts;
    std::vector<std::pair<msgpack::sbuffer*, IdClient> >cmds;


    template<typename ArgType>
    class	Callback : public ICallback
    {
    private:
      void (C::*callback)(IdClient, ArgType);
    public:
      Callback<ArgType>(void (C::*methodToCall)(IdClient, ArgType))
      {
	callback = methodToCall;
      }

      virtual void call(C* caller, IdClient idClient, msgpack::sbuffer* data) const
      {
	int size = data->size();
	ArgType arg;

	msgpack::unpacker pac;
	msgpack::unpacked result;
	
	// 
	
	//	std::cout << "taille attendue : " << data.size << std::endl;
	pac.reserve_buffer(size);
	memcpy(pac.buffer(), data->data(), size);
	pac.buffer_consumed(size);
	if (!pac.next(&result)) // bypass already parsed index
	  std::cout << "fuck pas d'id pas possible" << std::endl;

	if (pac.next(&result))
	  {
	    
	    msgpack::object obj = result.get();
	    obj = result.get();
	    try{
	      obj.convert(&arg);
	    }
	    catch(std::exception e)
	      {
		std::cout << "msgpack broken" << std::endl;
		return ; // FIXME: if you happen to be there, the communication might be broken thereafter.
	      }
	  }
	else
	  {
	    std::cout << "fuck pas d'arg pas possible" << std::endl;
	  }
	(caller->*callback)(idClient, arg);
      }
    };

    class	CallbackNoArg : public ICallback
    {
    private:
      void (C::*callback)(IdClient);
    public:
      CallbackNoArg(void (C::*methodToCall)(IdClient))
      {
	callback = methodToCall;
      }

      virtual void call(C* caller, IdClient idClient, msgpack::sbuffer*) const
      {
	(caller->*callback)(idClient);
      }
    };
  };
}

template<typename C, typename IdCom, typename IdClient>
Server::CommandManager<C, IdCom, IdClient>::CommandManager(C *c)
{
  caller = c;
}

template<typename C, typename IdCom, typename IdClient>
bool Server::CommandManager<C, IdCom, IdClient>::addCallback(IdCom commandId, ICallback* callback)
{
  boost::lock_guard<boost::mutex> lock(_m_fcts);

  if (fcts[commandId] == NULL)
    fcts[commandId] = callback;
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
void	Server::CommandManager<C, IdCom, IdClient>::addCommandToQueue(IdClient sender, char* cmd, int size)
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  
  msgpack::sbuffer* sbuf = new msgpack::sbuffer();
  sbuf->write(cmd, size);
  std::cout << "add command to queue: " << cmd << std::endl;
  cmds.push_back(std::pair<msgpack::sbuffer*, IdClient>(sbuf, sender));
}

template<typename C, typename IdCom, typename IdClient>
void	Server::CommandManager<C, IdCom, IdClient>::interpretCommands()
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  for (unsigned int i = 0; i < cmds.size(); i++)
    {
      std::cout << "commande appelee" << std::endl;
      IdCom id;
      int size = sizeof(IdCom);
      msgpack::unpacker pac;
      msgpack::unpacked result;
      
      pac.reserve_buffer(size);
      memcpy(pac.buffer(), cmds[i].first->data(), size);
      pac.buffer_consumed(size);
      if (pac.next(&result))
	{
	  msgpack::object obj = result.get();
	  obj.convert(&id);
	}
      std::cout << "id received : " << id << std::endl;
      if (fcts[(IdCom)id])
	fcts[(IdCom)id]->call(caller, cmds[i].second, cmds[i].first);
    }
  while (cmds.size() > 0)
    {
      delete cmds.back().first;
      cmds.pop_back();
    }
}

#endif
