#include "Socket.hh"

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

int Socket::Connect(std::string ip, int port)
{
  struct sockaddr_in addr;
  struct hostent *server;


  _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(_socket == -1)
    {
      std::cerr << "Erreur lors de la commande system socket" << std::endl;
      return -1;
    }

  addr.sin_addr.s_addr = inet_addr(ip.data());  
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  /* connect to host */
  if(connect(_socket, (struct sockaddr*)&addr,sizeof(addr)) == -1)
    {
      std::cerr << "Impossible de se connecter au MAster Serveur" << std::endl;
      return -1;
    }
  return 1;
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
  std::cout << _socket << ": " << "SIZE RECU " << nbRead << std::endl;
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

int Socket::sendToServer(const msgpack::sbuffer& cmd)
{
  int ret;

  //  std::cout << "commande envoyee au client : |" << cmd << "| de la taille : |" << cmd.size() << "|" << std::endl;
  ret = write(_socket, cmd.data(), cmd.size());
  return ret;
}
