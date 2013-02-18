#include <sstream>

std::string intToString(int nb)
{
    std::string s;
    std::stringstream out;

    out << nb;
    s = out.str();
    return (s);
}
