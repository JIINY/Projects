#include "IntInputHandler.hpp"
#include <string>
#include <utility>
#include <optional>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "InputParser.hpp"
using namespace std;


pair<ResultVariant, optional<int>> IntInputHandler::parseAsNumber(IntRule rule, const std::string& input)
{
	auto [parsingResult, num] = InputParser::parsingInputNumber(input);
	switch (parsingResult) {
	case IntParsingResult::EMPTY: return { InputResult::EMPTY_INT, num };
	case IntParsingResult::INVALID_CHAR: return { InputResult::INVALID_INT, num };
	case IntParsingResult::POSITIVE_NUMBER:
	case IntParsingResult::NEGATIVE_NUMBER:
	case IntParsingResult::ZERO:
	{
		InputResult ruleResult = validateIntRule(rule, num.value());
		return { ruleResult, num };
	}
	default: return{ InputResult::UNKNOWN, nullopt };
	}
}

InputResult IntInputHandler::validateIntRule(IntRule rule, int i)
{
	switch (rule) {
	case (IntRule::IntAll): return InputResult::SUCCESS;
	case (IntRule::PositiveOnly):
		return (i > 0) ? InputResult::SUCCESS : InputResult::WRONG_NUMBER;
	case (IntRule::NegativeOnly):
		return (i < 0) ? InputResult::SUCCESS : InputResult::WRONG_NUMBER;
	case (IntRule::ZeroOrPositive):
		return (i >= 0) ? InputResult::SUCCESS : InputResult::LENGTH_OVER;
	case (IntRule::ZeroOrNegative):
		return (i <= 0) ? InputResult::SUCCESS : InputResult::LENGTH_OVER;
	case (IntRule::NegativeOneToPositive):
		return (i >= -1) ? InputResult::SUCCESS : InputResult::LENGTH_OVER;
	default: return InputResult::UNKNOWN;
	}
}

