#include <iostream>
#include "Evaluator.h"
#include "ExpressionEvaluator.h"

using namespace std;

void TestEvaluator()
{
    ExpressionEvaluator ev("783+3 / (5^2)");
    EvaluationResult* result = ev.Compile();
    if(!result->success)
    {
        cout << "compile error:" << result->errorMsg << endl;
        delete result;
        return;
    }
    delete result;
    
    cout << "parsed: " << ev.Print() << endl;
    
    result = ev.Evaluate();
    if(!result->success)
    {
        cout << "runtime error:" << result->errorMsg << endl;
        delete result;
        return;
    }
    delete result;
    
    cout << "result=" << ev.GetResultDouble() << endl;
}

int main()
{
    
    //functions
    Evaluator e("/media/plenituz/DATA/C/codelite-worspace/MathEvaluator/test_prog", true);
    EvaluationResult* compile = e.Compile();
    if(!compile->success)
    {
        cout << "compile error:" << compile->errorMsg << endl;
        delete compile;
        return 0;
    }
    delete compile;
    
    cout << "parsed: " << e.Print() << endl;
    
    compile = e.EvaluateSource();
    if(!compile->success)
    {
        cout << "runtime error:" << compile->errorMsg << endl;
        delete compile;
        return 0;
    }
    delete compile;
    
    cout << "ran successfully: " << endl << e.Vars() << endl;
    
    return 0;
}