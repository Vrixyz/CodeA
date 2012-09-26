//
// Communication.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:24:59 2012 mathieu leurquin
// Last update Wed Sep 26 10:44:35 2012 thierry berger
//

#ifndef SERVER_COMMUNICATION_HPP
# define SERVER_COMMUNICATION_HPP

#include "../GameData/Command.hpp"
#include "tcp_connection.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <msgpack.hpp>
#include <map>

namespace Server
{
  class	Communication
  {
  public:
    std::map<int, tcp_connection::pointer> clients;

    Communication() : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242)), incr(0)
    {
    }

    /// return true to success, false if failed.
    bool sendToClient(const msgpack::sbuffer& packedInformation, int clientId);
    // GameData::Command* tryReceiveFromClient(int clientId);
    /// pointer, to "force" a variable to be sent to this function, which will contain the new clientId
    // bool tryAccept(int* clientId);
    void init();
    void start_accept();
    void handle_accept(tcp_connection::pointer& new_connection,
		       const boost::system::error_code& error);
    void addConnection(tcp_connection::pointer&);

    /// For thread:
    void accept_loop()
    {  
      io_service.run();
    }

    void	end()
    {
      thread_accept.join();
    }

  private:
    boost::thread thread_accept;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;
    mutable boost::mutex _m_clients;
    mutable boost::mutex _m_incr;
    
    int	incr;
  };
}

#endif
