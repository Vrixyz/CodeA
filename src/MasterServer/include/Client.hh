#ifndef CLIENT_H_
#define CLIENT_H_

class Socket;

class Client
{
 public:
  ~Client();
  Socket*	getSocket();
  void		setSocket(Socket*);
 private:
  Socket*	_soc;
};

#endif
