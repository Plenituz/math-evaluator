#pragma once

#include <string>
#include <vector>
#include "Token.h"
#include "Evaluator.h"

class ExpressionEvaluator
{
private:
    std::string expression;
    std::vector<Token*> tokens;
    NumberToken* result;
    
    unsigned int FindNextOperator();
    
public:
    ExpressionEvaluator(const std::string& expr);
    ExpressionEvaluator(std::vector<Token*>::iterator from, std::vector<Token*>::iterator to);
    EvaluationResult* Compile();
    EvaluationResult* Evaluate();
    NumberToken* EvaluateUnsafe();
    
    ~ExpressionEvaluator()
    {
        for(uint i = 0; i < tokens.size(); i++)
        {
            delete tokens[i];
        }
        tokens.clear();
        //result is part of tokens
    }
    
    double GetResultDouble()
    {
        return result->GetValue();
    }
    
    NumberToken* GetResult()
    {
        return result;
    }
    
    std::string Print()
    {
        std::stringstream s;
        for(uint i = 0 ; i < tokens.size(); i++)
        {
            s << " " << tokens[i]->Print();
        }
        return s.str();
    }
};