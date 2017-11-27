#pragma once
#include "Token.h"
#include <math.h>

class OperatorToken : public Token
{
public:
    virtual inline unsigned int Priority() = 0;
    virtual double Apply(double valBefore, double valAfter) = 0;
};

class AddToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore + valAfter;
    }
    
    virtual inline unsigned int Priority(){ return 1; }
    virtual const std::string Print()
    {
        return "[OP:+]";
    }
};

class SubstractToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore - valAfter;
    }
    virtual inline unsigned int Priority(){ return 1; }
    virtual const std::string Print()
    {
        return "[OP:-]";
    }
};

class DivideToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore / valAfter;
    }
    virtual inline unsigned int Priority(){ return 2; }
    virtual const std::string Print()
    {
        return "[OP:/]";
    }
};

class MultiplyToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore * valAfter;
    }
    virtual inline unsigned int Priority(){ return 2; }
    virtual const std::string Print()
    {
        return "[OP:*]";
    }
};

class PowerToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return std::pow(valBefore, valAfter);
    }
    virtual inline unsigned int Priority(){ return 3; }
    virtual const std::string Print()
    {
        return "[OP:^]";
    }
};