#include "Evaluator.h"
#include "Token.h"
#include "TokenBuilder.h"
#include <vector>
#include "CompileException.h"
#include <iostream>
#include <fstream>

using namespace std;

Evaluator::Evaluator(const std::string& str, bool isFile)
{
    if(!isFile)
    {
        expression = str;
    }
    else
    {
        ifstream file(str);
        string content;
        stringstream s;
        
        while(file >> content) 
        {
            s << content << ' ';
        }
        expression = s.str();
    }
}

EvaluationResult* Evaluator::Compile()
{
    TokenBuilder builder(&variables);
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

double Evaluator::GetVariable(std::string name)
{
    return variables[name];
}

void Evaluator::EvaluateSourceUnsafe()
{
    for(uint i = 0; i < tokens.size(); i++)
    {
        cout << "looking at " << tokens[i]->Print() << endl;
        
        NameToken* nameToken = dynamic_cast<NameToken*>(tokens[i]);
        if(nameToken != nullptr && i != tokens.size()-1)
        {
            //assign variable
            int nextEnd = FindEnd(i);
            if(nextEnd == -1)
                throw RuntimeException("no end of line after assignement expression " + nameToken->Print());
            //remember: token i is still the name token, so i + 1 is assign token, 
            //we evaluate after the assign token
            //and we don't take the end token in the evaluation so we stop at nextEnd - 1
            ExpressionEvaluator exprEv(tokens.begin() + i + 2, tokens.begin() + nextEnd);
            cout << "assigning this :" << endl;
            cout << exprEv.Print() << endl;
            double evaluated = exprEv.EvaluateUnsafe()->GetValue();
            nameToken->SetValue(evaluated);
            
            i += nextEnd - i;
        }
    }
}

int Evaluator::FindEnd(unsigned int from)
{
    //return the index of the next EndToken
    for(uint i = from; i < tokens.size(); i++)
    {
        EndToken* end = dynamic_cast<EndToken*>(tokens[i]);
        if(end != nullptr)
            return i;
    }
    return -1;
}

EvaluationResult* Evaluator::EvaluateSource()
{
    try
    {
        EvaluateSourceUnsafe();
        return new EvaluationResult();
    }
    catch(RuntimeException e)
    {
        return new EvaluationResult(e.what());
    }
}
