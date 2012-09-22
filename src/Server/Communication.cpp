//
// Communication.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 19:13:12 2012 thierry berger
// Last update Tue Sep 18 15:34:04 2012 thierry berger
//

#include "Communication.hpp"

void	Server::Communication::init()
{
  this->start_accept();
  // std::cout << "hello." << std::endl;
  /// TODO: create a thread to manage connections
  thread_accept = boost::thread(&Server::Communication::accept_loop, this);
  
  // std::cout << "hello?" << std::endl;
}

void Server::Communication::sendToClient(const msgpack::sbuffer& packedInformation, int clientId)
{
  try
    {
      boost::system::error_code ignored_error;
      
      /// TODO: send packed info :  boost::asio::buffer(static_cast<const void*>(&packedInformation))
      //      boost::asio::buffer b; //();
      // clients[clientId]->send(, packedInformation.size());
      boost::asio::write(clients[clientId]->socket(), boost::asio::buffer(packedInformation.data(), packedInformation.size()), ignored_error);
     // boost::asio::write(clients[clientId]->socket(), boost::asio::buffer(static_cast<const void*>(&packedInformation), packedInformation.size()), ignored_error);
      std::cout.write((packedInformation.data()), packedInformation.size());
      std::cout << std::endl;
      // std::cout << "packetSize: " << packedInformation.size() << std::endl;
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
}

// GameData::Command* Server::Communication::*tryReceiveFromClient(int clientId)
// {
//   return 0;
// }

void Server::Communication::start_accept()
{
  tcp_connection::pointer new_connection =
    tcp_connection::create(*this, acceptor.get_io_service());

  acceptor.async_accept(new_connection->socket(),
			boost::bind(&Server::Communication::handle_accept, this, new_connection,
				    boost::asio::placeholders::error));
}

void Server::Communication::handle_accept(tcp_connection::pointer& new_connection,
					  const boost::system::error_code& error)
{
  if (!error)
    {
      /// FIXME: not thread safe.
      clients[incr++] = new_connection;
      // new_connection->start();
    }
  start_accept();
}
