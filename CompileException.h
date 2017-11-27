#pragma once
#include <string>
#include <exception>

class CompileException: public std::exception
{
protected:
    std::string message;
    
public:
    CompileException(const std::string& msg) : message(msg){}
    
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

class RuntimeException: public std::exception
{
protected:
    std::string message;
    
public:
    RuntimeException(const std::string& msg) : message(msg){}
    
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};
