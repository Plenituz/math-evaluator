#pragma once
#include "Token.h"
#include "Evaluator.h"

class CodeBlockToken : public Token
{
private:
    Evaluator* evaluator;
    
public:
    CodeBlockToken(const std::string& expr)
    {
        evaluator = new Evaluator(expr);
        EvaluationResult* res = evaluator->Compile();
        if(!res->success)
        {
            std::string err = res->errorMsg;
            delete res;
            throw CompileException(err + " in code block " + expr);
        }
        delete res;
    }
    
    void Execute()
    {
        evaluator->EvaluateSourceUnsafe();
    }
};