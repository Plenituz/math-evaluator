#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "CompileException.h"

enum TokenType
{
    Value,
    Operator
};

class Token
{
public:
    bool valid = true;
    virtual ~Token(){}
    virtual const std::string Print(){ return "[NO PRINT]"; }
};

class NumberToken : public Token
{
protected:
    double value;
    NumberToken(){}
public:
    NumberToken(double val) : value(val){}
    virtual double GetValue(){return value;}
    virtual const std::string Print()
    {
        std::stringstream s;
        s << "[VALUE:" << value << "]";
        return s.str();
    }
};

class NameToken : public NumberToken
{
protected:
    std::map<std::string, double>* varDict;
    std::string name;
public:
    NameToken(const std::string& _name, std::map<std::string, double>* _varDict) : name(_name), varDict(_varDict){}
    
    virtual void SetValue(double val)
    { 
        (*varDict)[name] = val;
    }
    
    virtual double GetValue()
    {
        auto found = varDict->find(name);
        if(found == varDict->end())
            throw RuntimeException("variable " + name + " used but not initialized");
        return (*found).second;
    }
    
    virtual const std::string Print()
    {
        std::stringstream s;
        s << "[NAME:" << name << "]";
        return s.str();
    }
};

class AssignementToken : public Token
{
    virtual const std::string Print()
    {
        return "[ASSIGN:=]";
    }
};

class EndToken : public Token
{
    virtual const std::string Print()
    {
        return "[END:;]";
    }
};

class FunctionToken : public Token
{
private:
    std::string name;
    
public:
    FunctionToken(const std::string& _name) : name(_name){}
    std::string Name() { return name; }
    
    virtual const std::string Print()
    {
        return "[FUNC_DECL]";
    }
};

