#pragma once

#include "Token.h"
#include "OperatorToken.h"
#include "GroupToken.h"
#include <regex>
#include <map>

class TokenBuilder
{
private:
    std::map<std::string, double>* varDict;

    std::regex numberRegex = std::regex("\\d");
    std::regex operatorRegex = std::regex("(\\+|-|\\*|/|\\^)");
    std::regex nameRegex = std::regex("[a-zA-Z0-9_]");
    std::regex ignoredChars = std::regex("( |\n)");
   
    NumberToken* BuildNumberToken(const std::string& str, unsigned int& index);
    OperatorToken* BuildOperatorToken(const std::string& str, unsigned int& index);
    GroupToken* BuildGroupToken(const std::string& str, unsigned int& index);

    /** for each caracter starting at index test the regex and stop when the regex doesn't match anymore */
    std::string ExtractRegex(const std::string str, unsigned int& index, std::regex reg);
public:
    TokenBuilder(std::map<std::string, double>* _varDict) : varDict(_varDict){}
    ~TokenBuilder()
    {
    }
    std::vector<Token*> Parse(const std::string& str, unsigned int& index);
};