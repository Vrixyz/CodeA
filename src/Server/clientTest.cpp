//
// clientTest.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Fri Sep 14 12:40:33 2012 thierry berger
// Last update Fri Sep 14 15:07:12 2012 thierry berger
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <msgpack.hpp>

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
      for (;;)
	{
	  std::cout << "reading... ";
	  boost::array<char, 128> buf;
	  boost::system::error_code error;

	  size_t len = socket.read_some(boost::asio::buffer(buf), error);
	  if (error == boost::asio::error::eof)
	    break; // Connection closed cleanly by peer.
	  else if (error)
	    throw boost::system::system_error(error); // Some other error.
	  std::cout.write(buf.data(), len);
	  std::cout << std::endl;


	  void* buffer = buf.data();
	  std::cout << "OK (" << len << "): " << std::endl;

	  msgpack::unpacker pac;
 
	  // feeds the buffer.
	  pac.reserve_buffer(len);
	  std::cout << "segv?" << std::endl;
	  std::cout << pac.buffer() << " " << len << std::endl;
	  
	  memcpy(pac.buffer(), buffer, len);
	  std::cout << "segv?" << std::endl;
	  pac.buffer_consumed(len);
 
	  // now starts streaming deserialization.
	  msgpack::unpacked result;
	  while(pac.next(&result)) {
	    std::cout << result.get() << std::endl;
	  }

	  std::cout << std::endl;
	}
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  return 0;
}
