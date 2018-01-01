#include "string.h"

#include <cstdio>
#include <sstream>
#include <cstdarg>


std::string str_format(const char* fmt, va_list args)
{
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return std::string(buf);
}

std::string str_format(const char* fmt, ...)
{
    char buf[8192];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 8192, fmt, args);
    va_end(args);

    return std::string(buf);
}

std::vector<std::string>  split(std::string str, char delim)
{
    std::vector<std::string> elems;
    std::stringstream stream{str};
    std::string item;
    while(std::getline(stream, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}