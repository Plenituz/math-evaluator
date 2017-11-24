#pragma once

#include "Token.h"
#include "OperatorToken.h"
#include "GroupToken.h"
#include <regex>

class TokenBuilder
{
private:
    std::regex numberRegex = std::regex("\\d");
    std::regex operatorRegex = std::regex("(\\+|-|\\*|/)");
   
    NumberToken* BuildNumberToken(const std::string& str, unsigned int& index);
    OperatorToken* BuildOperatorToken(const std::string& str, unsigned int& index);
    GroupToken* BuildGroupToken(const std::string& str, unsigned int& index);

public:
    TokenBuilder(){}
    ~TokenBuilder()
    {
    }
    std::vector<Token*> Parse(const std::string& str, unsigned int& index);
};