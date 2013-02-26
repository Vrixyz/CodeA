#ifndef SOCKET_H_ 
#define SOCKET_H_

#include <iostream>
#include <string>

#include <msgpack.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <list>

#include "Client.hh"

#define BUFF 256

class Socket
{
 public:
  Socket();
  ~Socket();

  int	init();
  int	Bind(struct sockaddr_in);
  int	Listen(int);
  int	Select(int, fd_set *);
  int	Accept(struct sockaddr_in, int);
  void	Close();
  int	getFD();
  void	setIP(std::string ip){_ip = ip;}
  std::string	getIP(){ return _ip;}
  void	setFD(int fd);
  void	setNonBlock();

  int	RecvString(msgpack::sbuffer&);
  int	sendToServer(const msgpack::sbuffer&);

  private:
  int		_socket;
  std::string	_ip;
};

#endif
