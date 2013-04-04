#ifndef COMMAND_HPP_
# define COMMAND_HPP_

#include <msgpack.hpp>

namespace MasterData
{
  namespace Race
  {
    typedef enum Id_race
      {
	MAGE = 0,
	PORTAL = 1
      } race;
  }

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

	// communication with server


	REQUEST_SERVER = 10,	// COMMANDE DE CHOIX D'UN SERVEUR DE LA LISTE
	INFOS_SERVER = 11,	// REPONSE AVEC LES INFOS DE CONNEXIONS DU SERVER
	END_GAME = 12,		// COMMANDE CONFIRmANT LA FIN DE PARTI 
	END_GAME_SERV = 13,	// SERVEUR INFORMANT LE MASTER D'une FIN DE PARTIT SUIVIT PAR DES STRUCTURE DE RESUMER POUR LES DEUX CLIENT
	PLAYER_JOIN = 14,	// COMMANDE D'AJOUT A UN SERVEUR
	ENDGAME = 15,
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

  
  // END_GAME
  typedef struct endgame{
    int winner;
    int duree;
    // int nb_player ?
    
    MSGPACK_DEFINE(winner, duree);
  } EndGame;
  typedef struct endplayerdetails
  {
    int nbUnitKilled;
    //	nbunitkilled;
    //nbunitlost;
    //...

    MSGPACK_DEFINE(nbUnitKilled);
  } EndPlayerDetails;
  //

  //UNE PAR JOUEUR
  /*  struct	EndGame
  {
    EndGame(std::string _login, bool _win, int _r) :
      login(_login), win(_win), r(_r){}
    std::string login;
    bool	win;
    int		r;
    
    MSGPACK_DEFINE(login, win, r);
    };*/

}

#endif
