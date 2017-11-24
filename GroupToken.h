#pragma once

#include "Token.h"
#include "Evaluator.h"
#include <string>

class GroupToken : public NumberToken
{
private:
    Evaluator* evaluator;
public:
    GroupToken(const std::string& expr)
    {
        evaluator = new Evaluator(expr);
        EvaluationResult* res = evaluator->Compile();
        if(!res->success)
        {
            std::string err = res->errorMsg;
            delete res;
            throw err;
        }
        delete res;
    }
    
    ~GroupToken()
    {
        delete evaluator;
    }
    
    virtual double GetValue(){ return evaluator->Evaluate(); }
};