#pragma once

#include "Token.h"
#include "ExpressionEvaluator.h"
#include <string>
#include "CompileException.h"

class GroupToken : public NumberToken
{
private:
    ExpressionEvaluator* evaluator;
public:
    GroupToken(const std::string& expr)
    {
        evaluator = new ExpressionEvaluator(expr);
        EvaluationResult* res = evaluator->Compile();
        if(!res->success)
        {
            std::string err = res->errorMsg;
            delete res;
            throw CompileException(err + " in group " + expr);
        }
        delete res;
    }
    
    ~GroupToken()
    {
        delete evaluator;
    }
    
    virtual double GetValue()
    { 
        return evaluator->EvaluateUnsafe()->GetValue(); 
    }
    
    virtual const std::string Print()
    {
        std::stringstream s;
        s << "[GROUP START]" << evaluator->Print() << " [GROUP END]";
        return s.str();
    }
};