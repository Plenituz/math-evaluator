#include <iostream>
#include "TokenBuilder.h"
#include <sstream>

using namespace std;

vector<Token*> TokenBuilder::Parse(const std::string& str, unsigned int& index)
{
    vector<Token*> tokens;
    smatch match;
    
    while(index < str.size())
    {
        
        if(regex_match(str.begin() + index, str.begin() + index + 1, ignoredChars))
        {
            index++;
        }
        //doing the number check first assure variable names can't start with a number
        //but can still has a number in them
        else if(regex_match(str.begin() + index, str.begin() + index + 1, numberRegex))
        {
//            cout << "number " << str.substr(index, 1) << endl;

            tokens.push_back(BuildNumberToken(str, index));
        }
        else if(regex_match(str.begin() + index, str.begin() + index + 1, operatorRegex))
        {
//            cout << "operator " << str.substr(index, 1) << endl;
            tokens.push_back(BuildOperatorToken(str, index));
        }
        else if(str[index] == '(')
        {
//            cout << "group (" << endl;
            tokens.push_back(BuildGroupToken(str, index));
        }
        else if(regex_match(str.begin() + index, str.begin() + index + 1, nameRegex))
        {
//            cout << "name " << str.substr(index, 1) << endl;
            string name = ExtractRegex(str, index, nameRegex);
            if(name.compare("func") == 0)
                tokens.push_back(new FunctionToken(name));
            else
                tokens.push_back(new NameToken(name, varDict));
        }
        else if(str[index] == '=')
        {
//            cout << "assign =" << endl;
            tokens.push_back(new AssignementToken());
            index++;
        }
        else if(str[index] == ';')
        {
//            cout << "end ;" << endl;
            tokens.push_back(new EndToken());
            index++;
        }
        else
        {
            throw CompileException("token " + to_string(str[index]) + " unexpected");
            index++;
        }
    }
    
    return tokens;
}

NumberToken* TokenBuilder::BuildNumberToken(const string& str, unsigned int& index)
{
    string valueStr = ExtractRegex(str, index, numberRegex);
    double value = stod(valueStr);
    
//    cout << "built token " << value << " with " << valueStr << endl;
    
    return new NumberToken(value);
}

OperatorToken* TokenBuilder::BuildOperatorToken(const std::string& str, unsigned int& index)
{
    switch(str[index++])
    {
        case '+':
            return new AddToken();
        case '*':
            return new MultiplyToken();
        case '/':
            return new DivideToken();
        case '-':
            return new SubstractToken();
        case '^':
            return new PowerToken();
    }
    stringstream s;
    s << "operator " << str[index-1] << " not supported";
    throw CompileException(s.str());
}

GroupToken* TokenBuilder::BuildGroupToken(const std::string& str, unsigned int& index)
{
    unsigned int nbOpen = 0;
    index++;
    unsigned int startIndex = index;
    
       
    while(str.size() > index && (str[index] != ')' || nbOpen != 0))
    {           
        char c = str[index];
        if(c == '(')
            nbOpen++;
        if(c == ')')
            nbOpen--;
        index++;
    }
    
    if(nbOpen != 0 || str[index] != ')')
    {
        stringstream s;
        s << "parenthesis at " << startIndex << " never closed";
        throw CompileException(s.str());
    }
    
    string inGroup = str.substr(startIndex, index - startIndex);
    index++;
    return new GroupToken(inGroup);
}

std::string TokenBuilder::ExtractRegex(const std::string str, unsigned int& index, std::regex reg)
{
    unsigned int startIndex = index;
    
    //go to the end of the number 
    while(str.size() > index && regex_match(str.begin() + index, str.begin() + index + 1, reg))
    {
        index++;
    }

    string valueStr = str.substr(startIndex, index - startIndex);
    return valueStr;
}
