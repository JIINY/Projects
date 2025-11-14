#include "InputParser.hpp"
#include <utility>
#include <optional>
#include "InputTextUtils.hpp"
using namespace std;


pair<IntParsingResult, optional<int>> InputParser::parsingInputNumber(const string& input)
{
	int convertNum = atoi(input.c_str());

	string numCheck = InputTextUtils::getNegativeSub(input);
	bool isInputNumber = InputTextUtils::isAllDigits(numCheck);

	if (input.empty())
	{
		return { IntParsingResult::EMPTY, nullopt };
	}
	if (input[0] == '-' && isInputNumber)
	{
		return { IntParsingResult::NEGATIVE_NUMBER, convertNum };
	}
	if (InputTextUtils::isAllZero(input))
	{
		return { IntParsingResult::ZERO, 0 };
	}
	if (!isInputNumber)
	{
		return { IntParsingResult::INVALID_CHAR, nullopt };
	}

	return { IntParsingResult::POSITIVE_NUMBER, convertNum };
}

bool InputParser::isYes(const string& input) 
{
	string s = InputTextUtils::toUpper(input);
	if (s == "Y" || s == "YES")
	{
		return true;
	}
	return false;
}

bool InputParser::isNo(const string& input)
{
	string s = InputTextUtils::toUpper(input);
	if (s == "N" || s == "NO")
	{
		return true;
	}
	return false;
}

