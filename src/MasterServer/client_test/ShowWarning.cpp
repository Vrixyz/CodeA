#include "ShowWarning.h"

ShowWarning::ShowWarning(MyWindow* parent, std::string msg)
{
    _msg = msg;
    _parent = parent;
}

ShowWarning::~ShowWarning()
{
}

void    ShowWarning::setMsg(std::string msg)
{
    _msg = msg;
}

std::string ShowWarning::getMsg()
{
    return _msg;
}
