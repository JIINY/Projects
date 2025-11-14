#pragma once
#include <string>
#include <utility>
#include <optional>
#include <variant>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"

class IntInputHandler 
{
public:
	static std::pair<ResultVariant, std::optional<int>> parseAsNumber(IntRule rule, const std::string& input);

private:
	static InputResult validateIntRule(IntRule rule, int i);
};

