#include <sstream>
#include <string>

std::string intToString(int nb)
{
    std::string s;
    std::stringstream out;

    out << nb;
    s = out.str();
    return (s);
}

int         stringToInt(std::string toConv)
{
    int toRet;
    std::istringstream ss(toConv);

    ss >> toRet;
    return (toRet);
}
