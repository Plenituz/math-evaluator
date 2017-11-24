#include <iostream>
#include "Evaluator.h"

using namespace std;

int main()
{
    
    Evaluator e("783+3 / (5*2)");
    EvaluationResult* compile = e.Compile();
    
    if(!compile->success)
    {
        cout << "error:" << compile->errorMsg << endl;
        return 0;
    }
    
    double res = 0;
    try
    {
        res = e.Evaluate();
        cout << "res=" << res << endl;
    }
    catch(const char* e)
    {
        cout << "error:" << e << endl;
    }
    
    return 0;
}