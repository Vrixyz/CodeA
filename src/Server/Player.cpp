//
// Player.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 16:26:49 2012 thierry berger
// Last update Wed Sep 12 18:09:10 2012 thierry berger
//

#include "Player.hpp"

b2Body&	Server::Player::addUnit(b2Body& unit)
{
  units.push_back(&unit);
  return unit;
}
