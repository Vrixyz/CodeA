//
// mainTest.cpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 16:40:52 2012 thierry berger
// Last update Thu Nov  8 10:41:24 2012 mathieu leurquin
//

#include "World.hpp"
#include <iostream>
#include <msgpack.hpp>
#include <string>

int	main(int ac, char **av)
{
  if (ac < 3)
    {
      std::cout << av[0] << " serverPort masterPort masterIp" << std::endl;
      return 0;
    }
  Server::World w(atoi(av[1]));

  w.init(atoi(av[2]), av[3], 100, 100);
  w.run();
  return 0;
}
