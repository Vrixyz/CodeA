#ifndef STORE_H
#define STORE_H

#include "Network.h"

class Store
{

public:

    Store();
    ~Store();

    Network *getNetwork(void);
    std::string getServIP(void);
    std::string getLogin(void);
    std::string getClass(void);
    int getServPort(void);

    void setNetwork(Network*);
    void setLogin(std::string);
    void setClass(std::string);
    void setServIP(std::string);
    void setServPort(int);

private:

    Network     *_netw;
    int         _port;
    std::string _ip;
    std::string _class;
    std::string _login;

};

#endif // STORE_H
