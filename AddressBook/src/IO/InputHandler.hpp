#pragma once
#include <string>
#include <variant>
#include <optional>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "InputTextSource.hpp"
#include "StringInputHandler.hpp"


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
    ResultVariant getInt(IntRule rule, int& output);
    ResultVariant getInt(IntRule rule, const std::string& input, int& output);

    ResultVariant getChar(char& output);
    ResultVariant getChar(const std::string& input, char& output);

    ResultVariant getString(StringRule rule, std::string& output);
    ResultVariant getString(StringRule rule, const std::string& input, std::string& output);

    ResultVariant askYesNo();
    ResultVariant askYesNo(const std::string& input);

    bool getAnyKey();

    PagingPhase getViewPagingInput();
    PagingPhase getSearchPagingInput(int& output);

private:
    InputTextSource textSource_{};

    ResultVariant parsingInt(IntRule rule, const std::string& input, int& output);
    ResultVariant parsingChar(const std::string& input, char& output);
    ResultVariant parsingString(StringRule rule, const std::string& input, std::string& output);
    ResultVariant parsingYesNo(const std::string& input);
    bool parsingPagingCommand(PagingPhase& phase, std::string& input);
};

