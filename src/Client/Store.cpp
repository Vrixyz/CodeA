#include "Store.h"

Store::Store()
{
}

Store::~Store()
{
}

void Store::setNetwork(Network *netw)
{
    _netw = netw;
}

Network *Store::getNetwork(void)
{
    return _netw;
}

void Store::setLogin(std::string login)
{
    _login = login;
}

std::string Store::getLogin(void)
{
    return (_login);
}

void Store::setServPort(int port)
{
    _port = port;
}

int Store::getServPort(void)
{
    return (_port);
}

void Store::setServIP(std::string ip)
{
    _ip = ip;
}

std::string Store::getServIP(void)
{
    return (_ip);
}

void Store::setClass(std::string clas)
{
    _class = clas;
}

std::string Store::getClass(void)
{
    return (_class);
}
