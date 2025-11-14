#pragma once
#include <string>


class InputTextUtils
{
public:
    static std::string getNegativeSub(const std::string& input);
    static bool isAllDigits(const std::string& str);
    static bool isAllZero(const std::string& str);
    static std::string toUpper(const std::string& input);
};

