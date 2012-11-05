//
// Communication.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:24:59 2012 mathieu leurquin
// Last update Tue Oct 30 16:20:37 2012 mathieu leurquin
//

#ifndef SERVER_COMMUNICATION_HPP
# define SERVER_COMMUNICATION_HPP

#include "../GameData/Command.hpp"
#include "tcp_connection.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread.hpp>
#include <msgpack.hpp>
#include <map>
#include <vector>

namespace Server
{
  class	Communication
  {
  public:
    mutable boost::mutex _m_clients;
    std::list<int> clientsErase;
    std::map<int, tcp_connection::pointer> clients;
    std::vector<std::pair<GameData::Command, tcp_connection::pointer> >cmds;
    boost::array<char, 127> buf;
    Communication() : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4242))
    {
    }

    /// return true to success, false if failed.
    bool sendToClient(const msgpack::sbuffer& packedInformation, int clientId);
    /// pointer, to "force" a variable to be sent to this function, which will contain the new clientId
    // bool tryAccept(int* clientId);
    void init();
    void start_accept();
    void handle_accept(tcp_connection::pointer& new_connection,
		       const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error, std::size_t size);
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
    
    class read_socket_handler
    {
    public:
      read_socket_handler(Server::tcp_connection::pointer& connection, Communication *c) : _connection(connection), _com(c) {}
      
      void operator()(
		      const boost::system::error_code& ec,
		      std::size_t size)
      {
	msgpack::unpacker pac;
	msgpack::unpacked result;
	
	pac.reserve_buffer(size);
	memcpy(pac.buffer(), buf.elems, size);
	pac.buffer_consumed(size);
	if (pac.next(&result))
	  {
	    GameData::Command c;
	    msgpack::object obj = result.get();
	    obj.convert(&c);
	    _command = c;
	    boost::lock_guard<boost::mutex> lock(_com->_m_clients);
	    _com->cmds.push_back(std::pair<GameData::Command, tcp_connection::pointer>(c, _connection));	    
	  }
	setHandler();
      }
      
      void	setHandler()
      {
	_connection->socket().
	  async_read_some(boost::asio::buffer(buf, 127),
			  bind(boost::type<void>(), boost::ref(*this), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
      }
    
      GameData::Command &getCommand(){return _command;}
      Server::tcp_connection::pointer &getConnection(){return _connection;}
      
    private:
      boost::array<char, 127> buf;
      GameData::Command _command;
      Server::tcp_connection::pointer _connection;
      Communication *_com;
    };
  };
}

#endif
