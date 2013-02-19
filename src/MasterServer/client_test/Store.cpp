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
