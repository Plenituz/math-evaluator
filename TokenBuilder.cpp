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
        if(regex_match(str.begin() + index, str.begin() + index + 1, numberRegex))
        {
            cout << "number " << str.substr(index, 1) << endl;

            tokens.push_back(BuildNumberToken(str, index));
        }
        else if(regex_match(str.begin() + index, str.begin() + index + 1, operatorRegex))
        {
            cout << "operator " << str.substr(index, 1) << endl;
            tokens.push_back(BuildOperatorToken(str, index));
        }
        else if(str[index] == '(')
        {
            cout << "group (" << endl;
            tokens.push_back(BuildGroupToken(str, index));
        }
        else
        {
            cout << "no match for " << str.substr(index, 1) << endl;
            index++;
        }
    }
    
    return tokens;
}

NumberToken* TokenBuilder::BuildNumberToken(const string& str, unsigned int& index)
{
    int startIndex = index;
    
    //go to the end of the number 
    while(str.size() > index && regex_match(str.begin() + index, str.begin() + index + 1, numberRegex))
    {
        index++;
    }

    string valueStr = str.substr(startIndex, index - startIndex);
    double value = stod(valueStr);
    
    cout << "built token " << value << " with " << valueStr << endl;
    
    return new NumberToken(value);
}

OperatorToken* TokenBuilder::BuildOperatorToken(const std::string& str, unsigned int& index)
{
    cout << "building operator with " << str[index] << endl;
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
    }
    stringstream s;
    s << "operator " << str[index-1] << " not supported";
    throw s.str();
}

GroupToken* TokenBuilder::BuildGroupToken(const std::string& str, unsigned int& index)
{
    unsigned int nbOpen = 0;
    unsigned int startIndex = index;
    
    while(str.size() > index && (str[index] != ')' || nbOpen != 0))
    {
        if(str[index] == '(')
            nbOpen++;
        if(str[index] == ')')
            nbOpen--;
        index++;
    }
    
    if(nbOpen != 0 || str[index-1] != ')')
    {
        stringstream s;
        s << "parenthesis at " << startIndex << " never closed";
        throw s.str();
    }
    
    string inGroup = str.substr(startIndex+1, index - startIndex - 2);
    return new GroupToken(inGroup);
}
