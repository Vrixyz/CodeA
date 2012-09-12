//
// Communication.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:24:59 2012 mathieu leurquin
// Last update Wed Sep 12 13:28:59 2012 mathieu leurquin
//

#ifndef SERVER_COMMUNICATION_HPP
# define SERVER_COMMUNICATION_HPP

#include "../GameData/Command.hpp"

namespace Server
{
  class	Communication
  {
  public:
    void sendToClient(void *serializedInformation, int lenght, int clientId);
    Command *tryReceiveFromClient(int &clientId);
  };
}

#endif
