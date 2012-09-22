//
// BitField.hpp for  in /home/leurqu_m//Documents/tek3/pfa/CodeA/src/Server
// 
// Made by mathieu leurquin
// Login   <leurqu_m@epitech.net>
// 
// Started on  Tue Sep 18 10:58:04 2012 mathieu leurquin
// Last update Tue Sep 18 11:23:56 2012 mathieu leurquin
//

#ifndef SERVER_BITFIELD_HPP
# define SERVER_BITFIELD_HPP

namespace Server
{
  class BitField
  {
  private:
    char _bitField;
  public:
    BitField() : _bitField (0) {}
    
    void set(int position);
    void unset(int position);
    int get(int position);
  };
}

#endif
