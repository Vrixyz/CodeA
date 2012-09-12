//
// Bullet.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 16:08:13 2012 thierry berger
// Last update Wed Sep 12 17:52:53 2012 thierry berger
//

#ifndef GAME_DATA_BULLET_HPP
# define GAME_DATA_BULLET_HPP

namespace GameData
{
  struct Bullet
  {
    Bullet(int _damage) : damage(_damage) {}
    int damage;
    /// ? add life (for range or destroy while alive)
  };
}

#endif
