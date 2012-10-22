//
// mainTest.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 16:40:52 2012 thierry berger
// Last update Wed Oct 17 10:57:53 2012 mathieu leurquin
//

#include "World.hpp"
#include <iostream>
#include <msgpack.hpp>
#include <string>

int	main()
{
  Server::World w;

  w.init(100, 100);
  // msgpack::sbuffer buffer;
  // msgpack::packer<msgpack::sbuffer> pk(&buffer);
  // w.serialize(pk);


  // // deserializes these objects using msgpack::unpacker.
  // msgpack::unpacker pac;
 
  // // feeds the buffer.
  // pac.reserve_buffer(buffer.size());
  // memcpy(pac.buffer(), buffer.data(), buffer.size());
  // pac.buffer_consumed(buffer.size());
 
  // // now starts streaming deserialization.
  // msgpack::unpacked result;
  // while(pac.next(&result)) {
  //   std::cout << result.get() << std::endl;
  // }
  w.run();
  return 0;
}
