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

#include "tcp_connection.hpp"
#include <msgpack.h>

namespace Server
{
  class World;
  class CommandManager
  {
  public:
    CommandManager(World *w);
    // returns false in case of idCommand already handled. In this case, call removeCallBack first.
    bool addCallback(GameData::Command::Id commandId, void (World::*methodToCall)(char*));
    void removeCallback(GameData::Command::Id commandId);

    // called by Communication
    void addCommandToQueue(tcp_connection::pointer sender, boost::array<char, 127> cmd); // msgpack::sbuffer ou equivalent (suite du packet envoye apres l'id de la commande
    
    // will call adequate world functions to prepare the next update (function pointer)
    // then will delete handled commands
    // /!\ must be thread safe
    void interpretCommands();
    // on choppe l'id
    // on appelle la methode de w
  private:
    World *world;
    mutable boost::mutex _m_cmds;
    mutable boost::mutex _m_fcts;
    std::map<GameData::Command::Id, void (World::*)(char*)> fcts;
    std::vector<std::pair<boost::array<char, 127>, tcp_connection::pointer> >cmds;
  };
}

#include "World.hpp"

#endif
