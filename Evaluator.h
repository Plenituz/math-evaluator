#pragma once

#include <string>
#include "Token.h"
#include <vector>
#include <map>

class EvaluationResult;
class Token;

class Evaluator
{
private:
    std::string expression;
    std::vector<Token*> tokens;
    std::map<std::string, double> variables;
    
    void EvaluateSourceUnsafe();
    unsigned int FindNextOperator();
    int FindEnd(unsigned int from);
public:

    Evaluator(const std::string& str, bool isFile);
    
    //right now compiling is actually just parsing
    //therefore the compiler doesn't actually enforce 
    //any syntax rule
    //might change in the futur if I really want to push this project far 
    //probably not tho
    EvaluationResult* Compile();
    EvaluationResult* EvaluateSource();
    double GetVariable(std::string name);
    
    std::string Print()
    {
        std::stringstream s;
        for(uint i = 0 ; i < tokens.size(); i++)
        {
            s << " " << tokens[i]->Print();
            if(tokens[i]->Print().compare("[END:;]") == 0)
            {
                //quick hack for better debug displaying
                s << std::endl;
            }
        }
        return s.str();
    }
    
    std::string Vars()
    {
        std::stringstream s;
        s << "{" << std::endl;
        for(auto it = variables.begin(); it != variables.end(); it++)
        {
            s << "    " << (*it).first << "=" << (*it).second << std::endl;
        }
        s << "}";
        return s.str();
    }
};

class EvaluationResult
{
public:
	bool success;
	std::string errorMsg;
    
    EvaluationResult(const std::string& error) : success(false), errorMsg(error){}
    EvaluationResult() : success(true){}
};