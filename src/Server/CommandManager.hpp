#ifndef COMMAND_MANAGER_HPP
# define COMMAND_MANAGER_HPP

class CommandManager
{
public:
  World& w;
  // called by Communication
  void	addCommandToQueue(tcp_connection::pointer sender, msgpack::sbuffer cmd); // msgpack::sbuffer ou equivalent (suite du packet envoye apres l'id de la commande

  // will call adequate world functions to prepare the next update (function pointer)
  // then will delete handled commands
  // /!\ must be thread safe
  void interpretCommands()
  {
    // on choppe l'id
    // on appelle la methode de w
  }
};

#endif
