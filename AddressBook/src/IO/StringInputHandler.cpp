#include "StringInputHandler.hpp"
#include <string>
#include <utility>
#include <variant>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"
#include "../Common/VariantUtils.hpp"
using namespace std;


pair<ResultVariant, string> StringInputHandler::parseAsString(StringRule rule, const string& input)
{
	if (rule == StringRule::EmptyDisallow && input == "")
	{
		return { InputResult::EMPTY_STRING, input };
	}
	return {InputResult::SUCCESS, input };
}

