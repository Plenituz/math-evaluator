#include "Evaluator.h"
#include "Token.h"
#include "TokenBuilder.h"
#include <vector>

using namespace std;

EvaluationResult* Evaluator::Compile()
{
    TokenBuilder builder;
    unsigned int index = 0;
    try
    {
        tokens = builder.Parse(expression, index);
    }
    catch(string e)
    {
        return new EvaluationResult(e);
    }
    
	return new EvaluationResult();
}

double Evaluator::Evaluate()
{
    if(tokens.size() == 1)
    {
        NumberToken* result = dynamic_cast<NumberToken*>(tokens[0]);
        if(result == nullptr)
            throw "last token is not a number";
        return result->GetValue();
    }
    
    unsigned int next = FindNextOperator();
    if(next == 0 || next == tokens.size() - 1)
        throw "operator at the edge, an operator must be surrounded by values";
    
    NumberToken* valueBefore = dynamic_cast<NumberToken*>(tokens[next-1]);
    NumberToken* valueAfter = dynamic_cast<NumberToken*>(tokens[next+1]);
    OperatorToken* op = dynamic_cast<OperatorToken*>(tokens[next]);
    
    if(valueBefore == nullptr)
        throw "no value before operator at " + to_string(next);
    if(valueAfter == nullptr)
        throw "no value after operator at " + to_string(next);
    
    NumberToken* token = new NumberToken(op->Apply(valueBefore->GetValue(), valueAfter->GetValue()));
    tokens.erase(tokens.begin() + next - 1, tokens.begin() + next + 1);
    tokens[next - 1] = token;
    
    delete valueBefore;
    delete valueAfter;
    delete op;
    
    return Evaluate();
}

unsigned int Evaluator::FindNextOperator()
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
    {
        throw "no operator found";
    }
    return firstIndexOfHighest;
}
