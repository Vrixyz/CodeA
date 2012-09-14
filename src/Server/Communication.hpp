//
// Communication.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:24:59 2012 mathieu leurquin
// Last update Fri Sep 14 13:33:36 2012 thierry berger
//

#ifndef SERVER_COMMUNICATION_HPP
# define SERVER_COMMUNICATION_HPP

#include "../GameData/Command.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <msgpack.hpp>
#include <map>

namespace Server
{
  class	Communication
  {
  public:
    Communication() : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)) {}
    void sendToClient(const msgpack::sbuffer& packedInformation, int clientId);
    GameData::Command* tryReceiveFromClient(int clientId);
    /// pointer, to "force" a variable to be sent to this function, which will contain the new clientId
    bool tryAccept(int* clientId);
    std::map<int, boost::asio::ip::tcp::socket*> clients;
  private:
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;
  };
}

#endif
