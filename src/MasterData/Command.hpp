#ifndef COMMAND_HPP_
# define COMMAND_HPP_

#include <msgpack.hpp>

namespace MasterData
{
  // pluralized namespaces would be better but as a matter of coherency (regarding GameData::Command) we let them singular

  namespace Command
  {
    typedef enum Id_command
      {
	CONNECT_USER = 1,
	REGISTER_USER = 2,
	CONNECT_SERVER = 3
      } Id;
  }
}

#endif
