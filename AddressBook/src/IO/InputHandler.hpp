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

enum class PagingMenu 
{
    View,
    Search
};

enum class PagingPhase 
{
    Prev,
    Next,
    Exit,
    Error,
    Stay, //View전용
    PositiveNums, //여기부터 Search전용
    Enter
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
    PagingPhase getPagingInput(PagingMenu menu);
    int getPagingInt() { return this->num_; }
    ResultVariant getLastError() const { return this->lastError_; }

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
    int num_ = -1;
    char ch_ = '\0';
    std::string str_ = "";
    bool yesNo_ = false;
    ResultVariant lastError_;

    bool resolveCinFailed();
};
