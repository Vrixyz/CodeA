//
// Communication.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Wed Sep 12 13:24:59 2012 mathieu leurquin
// Last update Fri Nov  9 11:22:25 2012 mathieu leurquin
//

#ifndef SERVER_COMMUNICATION_HPP
# define SERVER_COMMUNICATION_HPP

#include "../GameData/Command.hpp"
#include "tcp_connection.hpp"
#include "CommandManager.hpp"

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/thread.hpp>
#include <map>
#include <vector>

namespace Server
{
  template<typename C>
  class	Communication
  {
  public:
    mutable boost::mutex _m_clients;
    std::map<int, tcp_connection::pointer> clients;
    std::list<int> clientsErase;
   // FIXME: ugly fixed size
    boost::array<char, 127> buf;
    CommandManager<C, int, int> *_command;
    Communication(int port = 4242) : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
    }

    /// pointer, to "force" a variable to be sent to this function, which will contain the new clientId
    // bool tryAccept(int* clientId);
    void init();
    void setCommandManager(CommandManager<C, int, int>* commandManager);

    /// return true to success, false if failed.
    bool sendToClient(const msgpack::sbuffer&packedInformation, int clientId);

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
      read_socket_handler(Server::tcp_connection::pointer& connection, Communication *c, int connectionId) : _connection(connection), _com (c), id(connectionId){}
      
      void operator()(const boost::system::error_code& ec, std::size_t size);
      
      void	setHandler()
      {
	_connection->socket().
	  async_read_some(boost::asio::buffer(buf, 127),
			  bind(boost::type<void>(), boost::ref(*this), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
      }
    
      Server::tcp_connection::pointer &getConnection(){return _connection;}
      const int id;
    private:
      boost::array<char, 127> buf;
      Server::tcp_connection::pointer _connection;
      Communication<C> *_com;
    };
  };
}


template<typename C>
void	Server::Communication<C>::init()
{
  this->start_accept();
  _command = NULL;
  // _command = new CommandManager<World, int, tcp_connection::pointer>(w);
  // _command->addCallback(GameData::Command::Fire, &World::fire);
  // _command->addCallback(GameData::Command::AimTo, &World::aimTo);
  // _command->addCallback(GameData::Command::MoveTo, &World::moveTo);
  // _command->addCallback(GameData::Command::Move, &World::askMove);
  // _command->addCallback(GameData::Command::RotateLeft, &World::rotateLeft);
  // _command->addCallback(GameData::Command::RotateRight, &World::rotateRight);
  // _command->addCallback(GameData::Command::RotateStop, &World::rotateStop);
  // _command->addCallback(GameData::Command::Shield, &World::shield);

  thread_accept = boost::thread(&Server::Communication<C>::accept_loop, this);
}

template<typename C>
void Server::Communication<C>::setCommandManager(CommandManager<C, int, int>* commandManager)
{
  _command = commandManager;
}

template<typename C>
bool Server::Communication<C>::sendToClient(const msgpack::sbuffer& packedInformation, int clientId)
{
  if (!clients[clientId])
    {
      std::cout<<"fin send (erased)"<<std::endl;
      return false;
    }
  try
    {
      boost::system::error_code ignored_error;
      // boost::lock_guard<boost::mutex> lock2(clients[clientId]->_mutex);
      boost::asio::write(clients[clientId]->socket(), boost::asio::buffer(packedInformation.data(), packedInformation.size()), ignored_error);
      if (ignored_error)
	{
	  /// FIXME: some errors might be more or less killing than others.
	  // clients[clientId].swap();
	  std::cout<<"erase..."<<std::endl;
	  
	  clientsErase.push_back(clientId);
	  clientsErase.unique();
	  std::cout<<"erased !"<<std::endl;
	  return false;
	}
    }
  catch (std::exception& e)
    {
      /// FIXME: I don't know how it could get here.
      std::cerr<<"Send to client fail : "<< e.what() << std::endl;
      exit(1);
    }
  return true;
}
template<typename C>
void Server::Communication<C>::start_accept()
{
  tcp_connection::pointer new_connection =
    tcp_connection::create(acceptor.get_io_service());
  
  acceptor.async_accept(new_connection->socket(),
			boost::bind(&Server::Communication<C>::handle_accept, this, new_connection,
				    boost::asio::placeholders::error));

}

template<typename C>
void Server::Communication<C>::handle_accept(tcp_connection::pointer& new_connection,
					  const boost::system::error_code& error)
{
  static int	incr = 0;


  if (!error)
    {
      boost::lock_guard<boost::mutex> lock(_m_clients);
      clients[incr] = new_connection;
  
      read_socket_handler* rsh = new read_socket_handler(new_connection, this, incr);
      
      rsh->setHandler();
      // FIXME: searching an empty slot woudl be better
      incr++;
    }
  start_accept();
}

template<typename C>
void Server::Communication<C>::read_socket_handler::operator()(const boost::system::error_code& ec, std::size_t size)
{
  // FIXME: data() should be copied
  _com->_command->addCommandToQueue(id, buf.data());
  setHandler();
}

#endif
