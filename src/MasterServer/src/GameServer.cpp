#include "../include/GameServer.hh"

GameServer::GameServer(int port, std::string name, int id)
{
  _name = name;
  _port = port;
  _id = id;
  _player = 0;
  std::cout << "NEW SERVEUR id:" << id << " name:" << name << " port:" << port << std::endl;
}

GameServer::~GameServer()
{
}
