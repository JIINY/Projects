#pragma once
#include <string>
#include <optional>
#include <utility>

enum class IntParsingResult
{
    POSITIVE_NUMBER,
    NEGATIVE_NUMBER,
    ZERO,
    EMPTY,
    INVALID_CHAR
};

class InputParser 
{
public:
    static std::pair<IntParsingResult, std::optional<int>> parsingInputNumber(const std::string& input);
    
    static bool isYes(const std::string& input);
    static bool isNo(const std::string& input);
};

