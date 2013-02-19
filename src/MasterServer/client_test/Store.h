#ifndef STORE_H
#define STORE_H

#include "Network.h"

class Store
{
public:
    Store();
    ~Store();
    void setNetwork(Network*);
    Network *getNetwork(void);
private:
    Network *_netw;
};

#endif // STORE_H
