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
  private:
    class read_socket_handler
    {
    public:
      read_socket_handler(Server::tcp_connection::pointer& connection, CommandManager<C, int, int> *manager, int connectionId) : _connection(connection), _manager (manager), id(connectionId)
{
  
}
      
      void operator()(const boost::system::error_code& ec, std::size_t size)
      {
	setHandler();
	std::cout << "recvd smth of size : " << size << std::endl;
	// FIXME: some errors might be less killing than others
	if (ec != NULL)
	  {
	    std::cout << "error: " << ec << std::endl;
	    return;
	  }
	// FIXME: data() should be copied
	
	_manager->addCommandToQueue(id, buf.data(), size);
      }
      
    
      Server::tcp_connection::pointer &getConnection(){return _connection;}
      void	setHandler()
      {
	_connection->socket().
	  async_read_some(boost::asio::buffer(buf, 127),
			  bind(boost::type<void>(), boost::ref(*this), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
      }
    private:
      boost::array<char, 127> buf;
      Server::tcp_connection::pointer _connection;
      CommandManager<C, int, int> *_manager;
      const int id;
    };

  public:
    mutable boost::mutex _m_clients;
    std::map<int, tcp_connection::pointer> clients;
    tcp_connection::pointer master;
    std::list<int> clientsErase;
   // FIXME: ugly fixed size
    boost::array<char, 127> buf;
    CommandManager<C, int, int> *_command;
    CommandManager<C, int, int> *_master_cmd;

    Communication(int port) : acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
    }

    /// pointer, to "force" a variable to be sent to this function, which will contain the new clientId
    // bool tryAccept(int* clientId);
    void init();
    void setCommandManager(CommandManager<C, int, int>* commandManager);
    void setCommandManagerMaster(CommandManager<C, int, int>* commandManager)
    {
      _master_cmd = commandManager;
    }

    /// return true to success, false if failed.
    bool sendToClient(const msgpack::sbuffer&packedInformation, int clientId);
    bool sendToMaster(const msgpack::sbuffer& packedInformation);

    void cleanClients();

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

    bool connect(int port, char* ip)
    {

      master = tcp_connection::create(acceptor.get_io_service());

      master->connect(ip, port);

      rsm = new read_socket_handler(master, _master_cmd, 0);
      rsm->setHandler();
      return true; // FIXME: bla

    }
    
  private:
    read_socket_handler* rsm;
    boost::thread thread_accept;
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor;

  };
}


template<typename C>
void	Server::Communication<C>::init()
{
  this->start_accept();
  _command = NULL;

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
      // std::cout<<"fin send (erased)"<<std::endl;
      return false;
    }
  try
    {
      boost::system::error_code ignored_error;
      // FIXME: that aint thread safe
      boost::asio::write(clients[clientId]->socket(), boost::asio::buffer(packedInformation.data(), packedInformation.size()), ignored_error);
      if (ignored_error)
	{
	  /// FIXME: some errors might be more or less killing than others.
	  // std::cout<<"prepare to erase..."<<std::endl;
	  clientsErase.push_back(clientId);
	  clientsErase.unique();
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
bool Server::Communication<C>::sendToMaster(const msgpack::sbuffer& packedInformation)
{
  try
    {
      boost::system::error_code ignored_error;
      // FIXME: that aint thread safe
      boost::asio::write(master->socket(), boost::asio::buffer(packedInformation.data(), packedInformation.size()), ignored_error);
      if (ignored_error)
	{
	  /// FIXME: some errors might be more or less killing than others.
	  // std::cout<<"prepare to erase..."<<std::endl;
	  exit(-42); // FIXME: that's ugly.
	  return false;
	}
    }
  catch (std::exception& e)
    {
      /// FIXME: I don't know how it could get here.
      std::cerr<<"Send to master fail : "<< e.what() << std::endl;
      exit(1);
    }
  return true;
}

template<typename C>
void	Server::Communication<C>::cleanClients()
{
  boost::lock_guard<boost::mutex> lock(_m_clients);
  for (std::list<int>::iterator it = clientsErase.begin(); it != clientsErase.end(); it++)
    {
      clients.erase(*it);
      // std::cout << "erased client " << *it << std::endl;
    }
  clientsErase.clear();
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
  
      read_socket_handler* rsh = new read_socket_handler(new_connection, _command, incr);
      
      rsh->setHandler();
      // FIXME: searching an empty slot would be better
      incr++;
    }
  start_accept();
}

#endif
