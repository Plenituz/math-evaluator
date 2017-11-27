#include "ExpressionEvaluator.h"
#include "TokenBuilder.h"
#include <string>
#include <iostream>

using namespace std;

ExpressionEvaluator::ExpressionEvaluator(const std::string& expr) : expression(expr)
{
}

ExpressionEvaluator::ExpressionEvaluator(std::vector<Token*>::iterator from, std::vector<Token*>::iterator to)
{
    tokens = vector<Token*>(from, to);
}

NumberToken* ExpressionEvaluator::EvaluateUnsafe()
{
    if(tokens.size() == 1)
    {
        NumberToken* result = dynamic_cast<NumberToken*>(tokens[0]);
        if(result == nullptr)
            throw RuntimeException("last token is not a number");
        return result;
    }
    
    unsigned int next = FindNextOperator();
    if(next == 0 || next == tokens.size() - 1)
        throw RuntimeException("operator at the edge, an operator must be surrounded by values");
    
    NumberToken* valueBefore = dynamic_cast<NumberToken*>(tokens[next-1]);
    NumberToken* valueAfter = dynamic_cast<NumberToken*>(tokens[next+1]);
    OperatorToken* op = dynamic_cast<OperatorToken*>(tokens[next]);
    
    if(valueBefore == nullptr)
        throw RuntimeException("no value before operator at " + to_string(next));
    if(valueAfter == nullptr)
        throw RuntimeException("no value after operator at " + to_string(next));
    
    NumberToken* token = new NumberToken(op->Apply(valueBefore->GetValue(), valueAfter->GetValue()));
    tokens.erase(tokens.begin() + next - 1, tokens.begin() + next + 1);
    tokens[next - 1] = token;
    
    delete valueBefore;
    delete valueAfter;
    delete op;
    
    return EvaluateUnsafe();
}

unsigned int ExpressionEvaluator::FindNextOperator()
{
    //go thought the tokens, find the first occurence of the highest priority
    unsigned int highestPriority = 0;
    int firstIndexOfHighest = -1;
    OperatorToken* op = nullptr;
    
    for(uint i = 0; i < tokens.size(); i++)
    {
        op = dynamic_cast<OperatorToken*>(tokens[i]);
        
        if(op != nullptr && op->Priority() > highestPriority)
        {
            highestPriority = op->Priority();
            firstIndexOfHighest = i;   
        }
    }
    
    if(firstIndexOfHighest == -1)
        throw RuntimeException("no operator found");
    
    return firstIndexOfHighest;
}

EvaluationResult* ExpressionEvaluator::Compile()
{
    TokenBuilder builder(nullptr);
    unsigned int index = 0;
    try
    {
        tokens = builder.Parse(expression, index);
    }
    catch(CompileException e)
    {
        return new EvaluationResult(e.what());
    }
    
    return new EvaluationResult();
}

EvaluationResult* ExpressionEvaluator::Evaluate()
{
    try
    {
        result = EvaluateUnsafe();
        return new EvaluationResult();
    }
    catch(RuntimeException e)
    {
        return new EvaluationResult(e.what());
    }
}


