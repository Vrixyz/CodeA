#include "./../include/Client.hh"
#include "./../include/Define.hh"
#include "./../include/Server.hh"

// CAN GO OUT
int	main(int ac, char **av)
{
  int port = 4242;
  if (ac == 2)
    port = atoi(av[1]);
  Server * server = new Server(port);

  std::cout << "INITIALISATION" << std::endl;
  if (server->Initialisation() == EXIT_ERROR)
    return EXIT_FAILURE;
  std::cout << "SUCCES" << std::endl;
  std::cout << "LANCEMENT DU MASTER SUR LE PORT " << port << std::endl;
  server->Run();
  return EXIT_SUCCESS;
}
