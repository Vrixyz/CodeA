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
}

bool Server::CommandManager::addCallback(GameData::Command::Id commandId, void (World::*methodToCall)(char*))
{
  boost::lock_guard<boost::mutex> lock(_m_fcts);

  if (fcts[commandId] == NULL)
    fcts[commandId] = methodToCall;
  else
    return false;
  return true;
}

void Server::CommandManager::removeCallback(GameData::Command::Id commandId)
{
  boost::lock_guard<boost::mutex> lock(_m_fcts);

  fcts.erase(commandId);
}
      
// TODO: addCommandToSend, and interpretCommandToSend, this would become addCommandReceived
void	Server::CommandManager::addCommandToQueue(tcp_connection::pointer sender, boost::array<char, 127> cmd)
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  cmds.push_back(std::pair<boost::array<char, 127>, tcp_connection::pointer>(cmd, sender));
}

void	Server::CommandManager::interpretCommands()
{
  boost::lock_guard<boost::mutex> lock(_m_cmds);
  for (unsigned int i = 0; i < cmds.size(); i++)
    {
      // TODO: seek directly asked unit (send unitId from client)
      int id;
      int size = 3;
      msgpack::unpacker pac;
      msgpack::unpacked result;
      
      pac.reserve_buffer(size);
      memcpy(pac.buffer(), cmds[i].first.data(), size);
      pac.buffer_consumed(size);
      if (pac.next(&result))
	{
	  msgpack::object obj = result.get();
	  obj.convert(&id);
	}
      // TODO: send id of client who has sent the data. (.second)
      ((world)->*fcts[(GameData::Command::Id)id])(cmds[i].first.data());
    }
  while (cmds.size() > 0)
    {
      cmds.pop_back();
    }
}
