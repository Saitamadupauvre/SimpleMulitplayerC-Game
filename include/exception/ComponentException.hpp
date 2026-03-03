#pragma once

#include <stdexcept>
#include <string>

class ComponentException : public std::exception
{
public:
    ComponentException(const std::string& msg): _msg(msg) {}
    const char* what() const noexcept override { return _msg.c_str(); }
private:
    std::string _msg;
};
