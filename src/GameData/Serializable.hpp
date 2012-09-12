//
// Serializable.hpp for  in /home/berger_t/PFA/src/GameData
// 
// Made by thierry berger
// Login   <berger_t@epitech.net>
// 
// Started on  Wed Sep 12 09:55:13 2012 thierry berger
// Last update Wed Sep 12 10:27:20 2012 thierry berger
//

#ifndef GAME_DATA_SERIALIZABLE_HPP
# define GAME_DATA_SERIALIZABLE_HPP

class	Serializable
{
public:
  void*	serialize(int& finalLength) const;
  static Serializable* unSerialize(void*);
};

#endif
