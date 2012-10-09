//
// clientTest.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Fri Sep 14 12:40:33 2012 thierry berger
// Last update Mon Oct  8 17:47:13 2012 mathieu leurquin
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <msgpack.hpp>
#include "../GameData/World.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
    {
      if (argc != 2)
	{
	  std::cerr << "Usage: client <host>" << std::endl;
	  return 1;
	}
      boost::asio::io_service io_service;
      tcp::resolver resolver(io_service);
      tcp::resolver::query query(argv[1], "4242");
      tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
      tcp::socket socket(io_service);
      boost::asio::connect(socket, endpoint_iterator);
      while (1)
	{
	  boost::system::error_code error;
	  std::cout << "reading... " << std::endl;
	  boost::array<char, 127> buf;

	  size_t len = socket.read_some(boost::asio::buffer(buf), error);
	  std::cout << "len: " << len << std::endl;
	  if (error == boost::asio::error::eof)
	    break; // Connection closed cleanly by peer.
	  else if (error)
	    throw boost::system::system_error(error); // Some other error.
	  std::cout.write(buf.data(), len);
	  std::cout << std::endl;


	  
	  
	  msgpack::unpacker pac;
 
	  // feeds the buffer.
	  pac.reserve_buffer(len);
	  
	  memcpy(pac.buffer(), buf.data(), len);
	  pac.buffer_consumed(len);
 
	  // now starts streaming deserialization.
	  msgpack::unpacked result;
	  if (pac.next(&result))
	    {
	      GameData::World woo;
	      msgpack::object obj = result.get();
	      obj.convert(&woo);
	      std::cout << "WORLD: [nbUnit: " << woo.nbUnit << ", nbElement: " << woo.nbElement << ", nbBullet: " << woo.nbBullet << "]" << std::endl;
	    }
	  while (pac.next(&result)) {
	    std::cout << result.get() << std::endl;
	  }
	  socket.close();
	  exit(1);
	}
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}
