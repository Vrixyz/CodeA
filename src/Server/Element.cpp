//
// Element.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 17:53:20 2012 thierry berger
// Last update Thu Sep 13 17:56:50 2012 thierry berger
//

#include "Element.hpp"

void Server::Element::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}

bool Server::Element::unSerialize(msgpack::packer<msgpack::sbuffer>& packet)
{
  return false;
}

int	Server::Element::getClassId() const
{
  return 0;
}
