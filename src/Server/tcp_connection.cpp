//
// tcp_connection.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Mon Sep 17 13:02:25 2012 thierry berger
// Last update Tue Sep 18 15:19:33 2012 thierry berger
//

#include "tcp_connection.hpp"

Server::tcp_connection::pointer Server::tcp_connection::create(boost::asio::io_service& io_service)
{
  return pointer(new tcp_connection(io_service));
}

boost::asio::ip::tcp::socket& Server::tcp_connection::socket()
{
  return socket_;
}

void Server::tcp_connection::start()
{
  // boost::asio::async_write(socket_, boost::asio::buffer("Hello world\n"),
  // 			   boost::bind(&tcp_connection::handle_write, shared_from_this(),
  // 				       boost::asio::placeholders::error,
  // 				       boost::asio::placeholders::bytes_transferred));
}

void Server::tcp_connection::handle_write(const boost::system::error_code& /*error*/,
					  size_t /*bytes_transferred*/)
{
  
}
