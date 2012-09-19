//
// Communication.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 19:13:12 2012 thierry berger
// Last update Tue Sep 18 10:42:02 2012 mathieu leurquin
//

#include "Communication.hpp"

bool	Server::Communication::tryAccept(int* clientId)
{
  boost::asio::ip::tcp::socket* s = new boost::asio::ip::tcp::socket(io_service);
  acceptor.accept(*s);
  /// FIXME: maybe clilentId shouldn't be set that dirtily
  clients[incr] = s;
  *clientId = incr++;
  return true;
}

void Server::Communication::sendToClient(const msgpack::sbuffer& packedInformation, int clientId)
{
  try
    {
      boost::system::error_code ignored_error;
      
      /// TODO: send packed info :  boost::asio::buffer(static_cast<const void*>(&packedInformation))
      //      boost::asio::buffer b; //();
      // clients[clientId]->send(, packedInformation.size());
      boost::asio::write(*(clients[clientId]), boost::asio::buffer(static_cast<const void*>(&packedInformation), packedInformation.size()), ignored_error);
      std::cout << "packetSize: " << packedInformation.size() << std::endl;
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

GameData::Command* Server::Communication::*tryReceiveFromClient(int clientId)
{
  return 0;
}
