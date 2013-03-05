#ifndef COMMAND_HPP_
# define COMMAND_HPP_

#include <msgpack.hpp>

namespace MasterData
{
  namespace Command
  {
    typedef enum Id_command
      {
	CONNECT_USER = 1,	// COMMANDE DE CONNEXION DE CLIENT
	REGISTER_USER = 2,	// COMMANDE D'INSCRIPTION DE CLIENT
	CONNECT_SERVER = 3,	// COMMANDE DE CONNEXION DE SERVER
	ASK_SERVER_LIST = 4,	// REQUETE DE LA LISTE DES SERVEUR
	SEND_SERVER_LIST = 5,	// REPONSE DE LA LISTE DES SERVER
	INFOS_CLIENT = 6,	// REPONSE DE CONNEXION 
	SEND_CHAT = 7,		// ENVOI DE MESSAGE DEPUIS UN CLIENT
	RECV_CHAT = 8,		// RECEPTION DU BROADCAST DE MESSAGE
	MATCHMAKING = 9,	// COMMANDE DE CHOIX DE SERVER DE MANIERE AUTO
	REQUEST_SERVER = 10,	// COMMANDE DE CHOIX D'UN SERVEUR DE LA LISTE
	INFOS_SERVER = 11,	// REPONSE AVEC LES INFOS DE CONNEXIONS DU SERVER
	END_GAME = 12,		// COMMANDE CONFIRmANT LA FIN DE PARTI 
	END_GAME_SERV = 13,	// SERVEUR INFORMANT LE MASTER D'une FIN DE PARTIT SUIVIT PAR DES STRUCTURE DE RESUMER POUR LES DEUX CLIENT
	PLAYER_JOIN = 14,	// COMMANDE D'AJOUT A UN SERVEUR

	ERROR = -1
      } Id;
  }

  struct	RecvChat
  {
    RecvChat(std::string _from, std::string _msg) :
      from(_from), msg(_msg){}
    std::string from;
    std::string msg;
    
    MSGPACK_DEFINE(from, msg);
  };

  struct	SendChat
  {
    SendChat(std::string _msg) :
      msg(_msg) {}
    std::string msg;
    
    MSGPACK_DEFINE(msg);
  };

  struct	ErrorMsg
  {
    ErrorMsg(std::string _msg) :
      msg(_msg) {}
    std::string msg;
    
    MSGPACK_DEFINE(msg);
  };
}

#endif
