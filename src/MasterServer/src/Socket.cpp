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

int Socket::Select(std::list<Socket *> _client, fd_set * _readfds)
{
  std::list<Socket *>::const_iterator	it;
  int		olderFd;
  unsigned int	i;

  olderFd = _socket;
  for (i = 0, it = _client.begin(); i < _client.size() ; it++, i++)
    if ((*it)->getFD() > olderFd)
      olderFd = (*it)->getFD();
  olderFd++;
  return select(olderFd, _readfds, NULL, NULL, NULL);
}

int Socket::Accept(struct sockaddr_in _sin_client, int _client_len)
{
	int ret;
	ret = accept(_socket, (struct sockaddr *)&_sin_client, (socklen_t *)&_client_len);
	return ret;
}

int Socket::RecvInt(int* cmd)
{
  int ret;

  ret = read(_socket, cmd, sizeof(int));
  return ret;
}

int Socket::RecvString(std::string &s1)
{
  char tmpBuff[BUFF];
  int nbRead;

  memset(tmpBuff, 0, BUFF);
  s1 = "";
  while ((nbRead = read(_socket, tmpBuff, BUFF)) > 0)
    {
      s1 += tmpBuff;
      memset(tmpBuff, 0, BUFF);
    }
  if (s1.size() > 0)
    nbRead = s1.size();
  std::cout << "END " << nbRead << std::endl;
  return nbRead;
}

int Socket::getFD()
{
  return _socket;
}

void Socket::setFD(int fd)
{
  int flags;

  _socket = fd;
  flags = fcntl (_socket, F_GETFL);
  fcntl (_socket, F_SETFL, flags | O_NONBLOCK);	 
}

int Socket::SendInt(int cmd)
{
  int ret;

  ret = write(_socket, &cmd, sizeof(int));
  return ret;
}

int Socket::SendString(std::string cmd)
{
  int ret;

  std::cout << "commande envoyee au client : |" << cmd << "| de la taille : |" << cmd.size() << "|" << std::endl;
  ret = write(_socket, cmd.data(), cmd.size());
  return ret;
}
