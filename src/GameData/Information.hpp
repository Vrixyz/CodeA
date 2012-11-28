#ifndef INFORMATION_HPP_
# define INFORMATION_HPP_

#include <msgpack.hpp>

namespace GameData
{
  // pluralized namespaces would be better but as a matter of coherency (regarding GameData::Command) we let them singular

  namespace InformationId
  {
    typedef enum e_Id
      {
	EntireWorld = 0,
	PlayerDefinition = 1
      } Id;
  }

  namespace Information
  {
    // TODO: there's also World, but we just send it as-is, would be a good idea to put a struct containing it here.

    struct PlayerDefinition
    {
      int idPlayer;
      // we could send team, nickname, ip (if authorized), whatever.
      
      MSGPACK_DEFINE(idPlayer);
    };
  }

}

#endif // INFORMATION_HPP_
