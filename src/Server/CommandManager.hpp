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

namespace Server
{
  class World;
  class CommandManager
  {
  public:
    World *world;
    std::map<GameData::Command::Type, void (World::*)(boost::array<char, 127>)> fcts;
    std::vector<std::pair<boost::array<char, 127>, tcp_connection::pointer> >cmds;
    CommandManager(World *w);
 // called by Communication
    void addCommandToQueue(tcp_connection::pointer sender, boost::array<char, 127> cmd); // msgpack::sbuffer ou equivalent (suite du packet envoye apres l'id de la commande
    
    // will call adequate world functions to prepare the next update (function pointer)
    // then will delete handled commands
    // /!\ must be thread safe
    void interpretCommands();
    // on choppe l'id
    // on appelle la methode de w
  };
}

#include "World.hpp"

#endif
