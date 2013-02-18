#ifndef SOCKET_H_ 
#define SOCKET_H_

#include <iostream>
#include <string>

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
  void	setFD(int fd);

  int	RecvString(std::string&);
  int	SendString(std::string);

  int	RecvInt(int*);
  int	SendInt(int);

  private:
  int	_socket;
};

#endif
