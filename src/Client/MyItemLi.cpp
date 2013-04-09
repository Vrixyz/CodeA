#include "MyItemLi.h"

MyItemLi::MyItemLi(int id)
{
    _id = id;
}

MyItemLi::~MyItemLi()
{
}

void    MyItemLi::setId(int id)
{
    _id = id;
}

int     MyItemLi::getId()
{
    return _id;
}
