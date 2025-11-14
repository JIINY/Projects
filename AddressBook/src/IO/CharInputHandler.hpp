#pragma once
#include <string>
#include <utility>
#include <optional>
#include <variant>
#include "../Common/ResultEnums.hpp"


class CharInputHandler 
{
public:
	static std::pair<ResultVariant, std::optional<char>> parseAsChar(const std::string& input);
};

