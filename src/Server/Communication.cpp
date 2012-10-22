//
// Communication.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 19:13:12 2012 thierry berger
// Last update Mon Oct 22 19:38:23 2012 mathieu leurquin
//

#include "Communication.hpp"

void	Server::Communication::init()
{
  this->start_accept();
  thread_accept = boost::thread(&Server::Communication::accept_loop, this);
}

bool Server::Communication::sendToClient(const msgpack::sbuffer& packedInformation, int clientId)
{
  try
    {
      boost::system::error_code ignored_error;
      
      boost::asio::write(clients[clientId]->socket(), boost::asio::buffer(packedInformation.data(), packedInformation.size()), ignored_error);
      if (ignored_error)
	{
	  /// FIXME: some errors might be more or less killing than others.
	  boost::lock_guard<boost::mutex> _m(_m_clients);
	  clients.erase(clientId);
	  return false;
	}
    }
  catch (std::exception& e)
    {
      /// FIXME: I don't know how it could get here.
      std::cerr << e.what() << std::endl;
      exit(1);
    }
  return true;
}

GameData::Command* Server::Communication::tryReceiveFromClient(int clientId)
{
  // try
 //    {
 //      boost::system::error_code error;
 //      boost::array<char, 127> buf;
      
 //      size_t len = clients[clientId]->socket().read_some(boost::asio::buffer(buf), error);
 //      if (error)
 // 	{
 // 	  boost::lock_guard<boost::mutex> _m(_m_clients);
 // 	  clients.erase(clientId);
 // 	  return 0;
 // 	}
 //      std::cout.write(buf.data(), len);
 //      std::cout << std::endl;
 //    }
 // catch (std::exception& e)
 //   {
 //     /// FIXME: I don't know how it could get here.
 //     std::cerr << e.what() << std::endl;
 //     exit(1);
 //   }
 return 0;
}

void Server::Communication::start_accept()
{
  tcp_connection::pointer new_connection =
    tcp_connection::create(*this, acceptor.get_io_service());
  
  acceptor.async_accept(new_connection->socket(),
			boost::bind(&Server::Communication::handle_accept, this, new_connection,
				    boost::asio::placeholders::error));

  // for (std::map<int, tcp_connection::pointer>::iterator
  // 	 it = clients.begin(); it != clients.end();
  //      it++)
  std::cout << "initialise" << std::endl;
}


class read_socket_handler
{
public:
  read_socket_handler(Server::tcp_connection::pointer& connection) : _connection(connection) {}

  void operator()(
		  const boost::system::error_code& ec,
		  std::size_t size)
  {
    std::string *s;
    msgpack::unpacker pac;
    msgpack::unpacked result;
    msgpack::sbuffer sbuf;

    std::cout << size << std::endl;
    // if (size == 0 || size == 3)
    //   return ;

    // pac.reserve_buffer(12);
    // memcpy(pac.buffer(), buf.data(), 12);
    // pac.buffer_consumed(12);
    // if (pac.next(&result))
    //   {
    // 	GameData::Command c;
    // 	msgpack::object obj = result.get();
    // 	std::cout << "getted" << std::endl;      
    // 	obj.convert(&c);
    // 	std::cout<<"Command : "<<c.type<<" "<<c.x<<" "<<c.y<<std::endl;
    //   }
    setHandler();
  }

  void	setHandler()
  {
    _connection->socket().
      async_read_some(boost::asio::buffer(buf, 127),
		      bind(boost::type<void>(), *this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }
private:
  boost::array<char, 127> buf;
  Server::tcp_connection::pointer _connection;
};

void Server::Communication::handle_accept(tcp_connection::pointer& new_connection,
					  const boost::system::error_code& error)
{
  if (!error)
    {
      boost::unique_lock<boost::mutex> lhs_lock(_m_clients, boost::defer_lock);
      boost::unique_lock<boost::mutex> rhs_lock(_m_incr, boost::defer_lock);
      boost::lock(lhs_lock, rhs_lock);
      /// FIXME: not thread safe.
      clients[incr++] = new_connection;
      // new_connection->start();
    }
  
  read_socket_handler* rsh = new read_socket_handler(new_connection);

  rsh->setHandler();
  start_accept();
}

void Server::Communication::handleRead(const boost::system::error_code& error, std::size_t size)
{
  std::string *s;
  msgpack::unpacker pac;
  msgpack::unpacked result;
  msgpack::sbuffer sbuf;

  std::cout << size << std::endl;
  if (size == 0 || size == 3)
    return ;

  pac.reserve_buffer(12);
  memcpy(pac.buffer(), buf.data(), 12);
  pac.buffer_consumed(12);
  if (pac.next(&result))
    {
      GameData::Command c;
      msgpack::object obj = result.get();
      std::cout << "getted" << std::endl;      
      obj.convert(&c);
      std::cout<<"Command : "<<c.type<<" "<<c.x<<" "<<c.y<<std::endl;
    }
}
