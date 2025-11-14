#include "CharInputHandler.hpp"
#include <string>
#include <optional>
#include <utility>
#include <variant>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"
using namespace std;


pair<ResultVariant, optional<char>> CharInputHandler::parseAsChar(const string& input) 
{
	if (input.empty())
	{
		return { InputResult::EMPTY_CHAR, nullopt };
	}
	else if (input.length() > 1)
	{
		return { InputResult::LENGTH_OVER, input[0] };
	}
	else if (!isalpha(static_cast<unsigned char>(input[0]))) //한글로 죽지 않도록 cast
	{
		return { InputResult::INVALID_CHAR, nullopt };
	}
	return { InputResult::SUCCESS, input[0] };
}

