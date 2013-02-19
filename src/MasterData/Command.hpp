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
	CONNECT_SERVER = 3,
	ASK_SERVER_LIST = 4,
	SEND_SERVER_LIST = 5,
	INFOS_CLIENT = 6,
	ERROR = -1
      } Id;
  }

  struct	ErrorMsg
  {
    ErrorMsg(std::string _msg) :
      msg(_msg) {}
    std::string msg;
    
    MSGPACK_DEFINE(msg);
  };
}

#endif
