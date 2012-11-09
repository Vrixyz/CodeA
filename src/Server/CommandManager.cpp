//
// CommandManager.cpp for  in /home/leurqu_m//Documents/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Thu Nov  8 10:24:02 2012 mathieu leurquin
// Last update Fri Nov  9 11:31:37 2012 mathieu leurquin
//

#include "CommandManager.hpp"


Server::CommandManager::CommandManager(World *w)
{
  world = w;
  fcts[GameData::Command::Fire] = &World::fire;
  fcts[GameData::Command::AimTo] = &World::aimTo;  
  fcts[GameData::Command::MoveTo] = &World::moveTo;
  fcts[GameData::Command::Move] = &World::askMove;
  fcts[GameData::Command::RotateLeft] = &World::rotateLeft;
  fcts[GameData::Command::RotateRight] = &World::rotateRight;
  fcts[GameData::Command::RotateStop] = &World::rotateStop;
  fcts[GameData::Command::Shield] = &World::shield;   
}

void	Server::CommandManager::addCommandToQueue(tcp_connection::pointer sender, boost::array<char, 127> cmd)
{
  cmds.push_back(std::pair<boost::array<char, 127>, tcp_connection::pointer>(cmd, sender));
}

void	Server::CommandManager::interpretCommands()
{
  for (std::map<int, tcp_connection::pointer>::const_iterator
	 it = this->world->communication.clients.begin(); it != this->world->communication.clients.end();
       it++)
    {
      for (unsigned int i = 0; i < cmds.size(); i++)
	{
	  if (cmds[i].second == it->second)
	    {
	      // TODO: seek directly asked unit (send unitId from client)
	      int id;
	      int size = 3;
	      msgpack::unpacker pac;
	      msgpack::unpacked result;
	      
	      pac.reserve_buffer(size);
	      memcpy(pac.buffer(), (cmds[i].first).elems, size);
	      pac.buffer_consumed(size);
	      if (pac.next(&result))
		{
		  std::cout<<"PASS"<<std::endl;
		  msgpack::object obj = result.get();
 		  obj.convert(&id);
		  std::cout<<"N°:"<<id<<std::endl;
		}
	      ((world)->*fcts[(GameData::Command::Type)id])(cmds[i].first);
	    }
	}
      while (cmds.size() > 0)
	{
	  cmds.pop_back();
	}
    }
}
