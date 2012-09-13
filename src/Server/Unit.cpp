//
// Unit.cpp for  in /home/berger_t//PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Thu Sep 13 13:21:11 2012 thierry berger
// Last update Thu Sep 13 17:48:53 2012 thierry berger
//

#include "Unit.hpp"

void	Server::Unit::addPlayer(Player* p)
{
  /// TODO: add only if not already in the list
  _data.playersId.push_back(p->id);
}

void Server::Unit::serialize(msgpack::packer<msgpack::sbuffer>& packet) const
{
  packet.pack(_data);
}
