//
// Communication.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 19:13:12 2012 thierry berger
// Last update Fri Nov  9 11:30:12 2012 mathieu leurquin
//

#include "Communication.hpp"

void	Server::Communication::init(World *w)
{
  this->start_accept();
  _command = new CommandManager(w);
  thread_accept = boost::thread(&Server::Communication::accept_loop, this);
}

bool Server::Communication::sendToClient(const msgpack::sbuffer& packedInformation, int clientId)
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
  static int	incr = 0;

  if (!error)
    {
      // boost::lock_guard<boost::mutex> lock(_m_clients);
      clients[incr++] = new_connection;
    }
  
  read_socket_handler* rsh = new read_socket_handler(new_connection, this);

  rsh->setHandler();
  start_accept();
}

void Server::Communication::read_socket_handler::operator()(const boost::system::error_code& ec, std::size_t size)
{
  // msgpack::sbuffer d;

  // memcpy(&d, buf.data(), size);
  // pac.reserve_buffer(size);
  // memcpy(pac.buffer(), buf.elems, size);
  // pac.buffer_consumed(size);
  // if (pac.next(&result))
  //   {
  //     GameData::Command c;
  //     msgpack::object obj = result.get();
  //     obj.convert(&c);
  //     _command = c;
  //     boost::lock_guard<boost::mutex> lock(_com->_m_clients);
  //   }
  
  _com->_command->addCommandToQueue(_connection, buf);
  setHandler();
}

