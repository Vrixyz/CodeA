#include "./../include/Socket.hh"

Socket::~Socket()
{
}

Socket::Socket()
{
}

void Socket::Close()
{
close(_socket);
}

int Socket::init()
{
  struct protoent	* pe;
  pe = getprotobyname("TCP");
  _socket = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  return _socket;
}

int Socket::Bind(struct sockaddr_in	 _sin)
{
  int	ret;

  ret = bind(_socket, (const struct sockaddr *)&_sin, sizeof(_sin));
  return ret;
}

int Socket::Listen(int _listenListSize)
{
  int	ret;

  ret = listen(_socket, _listenListSize);
  return ret;
}

int Socket::Select(int FD, fd_set * _readfds)
{
  return select(FD, _readfds, NULL, NULL, NULL);
}

int Socket::Accept(struct sockaddr_in _sin_client, int _client_len)
{
  int ret;
  ret = accept(_socket, (struct sockaddr *)&_sin_client, (socklen_t *)&_client_len);
  setIP(inet_ntoa(_sin_client.sin_addr));
 
  return ret;
}

int Socket::RecvString(msgpack::sbuffer &buff)
{
  char tmpBuff[BUFF];
  int nbRead;

  memset(tmpBuff, 0, BUFF);
  while ((nbRead = read(_socket, tmpBuff, BUFF)) > 0)
    {
      buff.write(tmpBuff, nbRead);
      memset(tmpBuff, 0, BUFF);    
    }
  if (buff.size() > 0)
    nbRead = buff.size();
  std::cout << _socket << ": " << "SIZE RECU " << nbRead << std::endl;
  return nbRead;
}

int Socket::getFD()
{
  return _socket;
}

void Socket::setFD(int fd)
{
  _socket = fd;
}

void Socket::setNonBlock()
{
  int flags;
 
  flags = fcntl (_socket, F_GETFL);
  fcntl (_socket, F_SETFL, flags | O_NONBLOCK);	 
}

int Socket::sendToServer(const msgpack::sbuffer& cmd)
{
  int ret;

  ret = write(_socket, cmd.data(), cmd.size());
  return ret;
}
