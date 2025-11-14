#pragma once
#include <string>
#include <utility>
#include <variant>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"


class StringInputHandler 
{
public:
	static std::pair<ResultVariant, std::string> parseAsString(StringRule rule, const std::string& input);
};

