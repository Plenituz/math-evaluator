#pragma once

#include <string>
#include "Token.h"
#include <vector>

class EvaluationResult;
class Token;

class Evaluator
{
private:
	std::string expression;
	bool compiled = false;
    std::vector<Token*> tokens;
    
    unsigned int FindNextOperator();
public:
	Evaluator(const std::string& expr)
    {
        expression.assign(expr);
    }
    
	EvaluationResult* Compile();
	double Evaluate();
};

class EvaluationResult
{
public:
	bool success;
	std::string errorMsg;
    
    EvaluationResult(const std::string& error) : success(false), errorMsg(error){}
    EvaluationResult() : success(true){}
};