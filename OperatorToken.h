#pragma once
#include "Token.h"

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
};

class SubstractToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore - valAfter;
    }
    virtual inline unsigned int Priority(){ return 1; }
};

class DivideToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore / valAfter;
    }
    virtual inline unsigned int Priority(){ return 2; }
};

class MultiplyToken : public OperatorToken
{
public:
    double Apply(double valBefore, double valAfter)
    {
        return valBefore * valAfter;
    }
    virtual inline unsigned int Priority(){ return 2; }
};