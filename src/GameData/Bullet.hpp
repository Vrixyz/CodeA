//
// Bullet.hpp for  in /home/berger_t/PFA/src/Server
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 16:08:13 2012 thierry berger
// Last update Fri Sep 14 11:09:01 2012 thierry berger
//

#ifndef GAME_DATA_BULLET_HPP
# define GAME_DATA_BULLET_HPP

#include <msgpack.hpp>

namespace GameData
{
  struct Bullet
  {
    Bullet(int _damage, int _id) : damage(_damage), id(_id) {}
    int damage;
    int id;
    /// ? add life (for range or destroy while alive)
    
    MSGPACK_DEFINE(damage, id);
  };
}

#endif
