#pragma once

enum TokenType
{
    Value,
    Operator
};

class Token
{
public:
    virtual ~Token(){}
};

class NumberToken : public Token
{
protected:
    double value;
    NumberToken(){}
public:
    NumberToken(double val) : value(val){}
    virtual double GetValue(){return value;}
};



