//
// tcp_connection.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Mon Sep 17 12:28:48 2012 thierry berger
// Last update Tue Sep 18 12:33:24 2012 thierry berger
//

#ifndef TCP_CONNECTION_HPP
# define TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

#include <iostream>

namespace Server
{
  class Communication;

  class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
  {
  public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(Communication& com, boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& socket();
    void start();
  private:
    tcp_connection(Communication& _com, boost::asio::io_service& io_service)
      : com(_com), socket_(io_service)
    {
    }
    void handle_write(const boost::system::error_code& /*error*/,
		      size_t /*bytes_transferred*/);
    Communication& com;
    boost::asio::ip::tcp::socket socket_;
  };
}

#include "Communication.hpp"

#endif
