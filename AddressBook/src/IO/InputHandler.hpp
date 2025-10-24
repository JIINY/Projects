#pragma once
#include <string>
#include <variant>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"


enum class IntRule 
{
    IntAll,
    PositiveOnly,
    NegativeOnly,
    ZeroOrPositive,
    ZeroOrNegative,
    NegativeOneToPositive,
};

enum class StringRule 
{
    EmptyAllow,
    EmptyDisallow
};


class InputHandler 
{
public:
    void getAnyKey();
    bool anyKeyOrQuit();
    int getInt(IntRule rule);
    char getChar();
    std::string getString(StringRule rule);
    bool askYesNo();
    ResultVariant getLastError() const;

protected:
    static std::string getNegativeSub(const std::string& input);
    static bool isAllDigits(const std::string& str);
    static bool isAllZero(const std::string& str);
    std::string toUpper(const std::string& input);
    IntParsingResult parsingInputNumber(const std::string& input, int& output);
    InputResult validateIntRule(int i, IntRule rule);

    ResultVariant waitForAnyKeyOrQuit();
    ResultVariant getInputString(StringRule rule);    
    ResultVariant getInputNumber(IntRule rule);
    ResultVariant getInputChar();
    ResultVariant getInputYesNo();


private:
    int num = -1;
    char ch = '\0';
    std::string str = "";
    bool yesNo = false;
    ResultVariant lastError;
};
