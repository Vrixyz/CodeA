//
// tcp_connection.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Mon Sep 17 12:28:48 2012 thierry berger
// Last update Tue Oct 30 14:42:01 2012 mathieu leurquin
//

#ifndef TCP_CONNECTION_HPP
# define TCP_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

#include <iostream>

namespace Server
{
  class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
  {
  public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    mutable boost::mutex _mutex;

    ~tcp_connection()
    {
      socket_.close();
    }
    static pointer create(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& socket();
    void start();
 private:
    tcp_connection(boost::asio::io_service& io_service)
      : socket_(io_service)
    {
    }
    void handle_write(const boost::system::error_code& /*error*/,
		      size_t /*bytes_transferred*/);
    boost::asio::ip::tcp::socket socket_;
  };
}

#endif
