#include "InputHandler.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <cctype>
#include "../Common/ResultEnums.hpp"
#include "../Common/RuleEnums.hpp"
#include "../Common/VariantUtils.hpp"
#include "InputTextSource.hpp"
#include "InputTextUtils.hpp"
#include "InputParser.hpp"
#include "IntInputHandler.hpp"
#include "CharInputHandler.hpp"
#include "StringInputHandler.hpp"
using namespace std;


ResultVariant InputHandler::getInt(IntRule rule, int& output)
{
	//입력
	auto [inputResult, input] = textSource_.readTextSource();
	if (inputResult == false)
	{
		return InputResult::FAIL;
	}

	return parsingInt(rule, input, output);
}

ResultVariant InputHandler::getInt(IntRule rule, const string& input, int& output)
{
	return parsingInt(rule, input, output);
}

ResultVariant InputHandler::parsingInt(IntRule rule, const std::string& input, int& output) 
{
	auto [parsingResult, parsingInt] = IntInputHandler::parseAsNumber(rule, input);
	if (isVariantEqualTo <InputResult>(parsingResult, InputResult::SUCCESS)
		|| isVariantEqualTo <InputResult>(parsingResult, InputResult::WRONG_NUMBER)
		|| isVariantEqualTo <InputResult>(parsingResult, InputResult::LENGTH_OVER))
	{
		output = parsingInt.value();
	}
	return parsingResult;
}


ResultVariant InputHandler::getChar(char& output)
{
	auto [inputResult, input] = textSource_.readTextSource();
	if (inputResult == false)
	{
		return InputResult::FAIL;
	}
	return parsingChar(input, output);
}

ResultVariant InputHandler::getChar(const string& input, char& output) 
{
	return parsingChar(input, output);
}

ResultVariant InputHandler::parsingChar(const string& input, char& output) 
{
	auto [parsingResult, parsingChar] = CharInputHandler::parseAsChar(input);
	if (isVariantEqualTo <InputResult>(parsingResult, InputResult::SUCCESS)
		|| isVariantEqualTo <InputResult>(parsingResult, InputResult::LENGTH_OVER))
	{
		output = parsingChar.value();
	}
	return parsingResult;
}


ResultVariant InputHandler::getString(StringRule rule, string& output)
{
	auto [inputResult, input] = textSource_.readTextSource();
	if (inputResult == false)
	{
		return InputResult::FAIL;
	}

	return parsingString(rule, input, output);
}

ResultVariant InputHandler::getString(StringRule rule, const string& input, string& output) 
{
	return parsingString(rule, input, output);
}

ResultVariant InputHandler::parsingString(StringRule rule, const string& input, string& output) 
{
	auto [parsingResult, parsingString] = StringInputHandler::parseAsString(rule, input);
	output = parsingString;
	return parsingResult;
}


ResultVariant InputHandler::askYesNo()
{
	auto [inputResult, input] = textSource_.readTextSource();
	if (inputResult == false)
	{
		return InputResult::FAIL;
	}

	return parsingYesNo(input);
}

ResultVariant InputHandler::askYesNo(const string& input) 
{
	return parsingYesNo(input);
}

ResultVariant InputHandler::parsingYesNo(const string& input) 
{
	if (input.empty())
	{
		return InputResult::EMPTY_STRING;
	}
	else if (InputParser::isYes(input))
	{
		return InputResult::YES;
	}
	else if (InputParser::isNo(input)) 
	{
		return InputResult::NO;
	}

	return InputResult::UNKNOWN;
}


bool InputHandler::getAnyKey()
{
	auto [inputResult, input] = textSource_.readTextSource();
	if (inputResult == false)
	{
		return false;
	}
	return true;
}


CommandPhase InputHandler::getViewPagingInput() 
{
	string input = "";
	ResultVariant inputResult = getString(StringRule::EmptyAllow, input);
	if (!isVariantEqualTo<InputResult>(inputResult, InputResult::SUCCESS))
	{
		return CommandPhase::Error;
	}

	CommandPhase phase;
	if (parsingPagingCommand(phase, input))
	{
		if (phase == CommandPhase::Enter) { return CommandPhase::Enter; }
		return phase;
	}
	return CommandPhase::Error;
}

CommandPhase InputHandler::getSearchPagingInput(int& output)
{
	string input = "";
	ResultVariant inputResult = getString(StringRule::EmptyAllow, input);
	if (!isVariantEqualTo<InputResult>(inputResult, InputResult::SUCCESS))
	{
		return CommandPhase::Error;
	}

	CommandPhase phase;
	if (parsingPagingCommand(phase, input)) { return phase; }
	else
	{
		auto [parsedResult, parsedInt] = InputParser::parsingInputNumber(input);
		if (parsedResult == IntParsingResult::POSITIVE_NUMBER)
		{
			output = parsedInt.value();
			return CommandPhase::PositiveNums;
		}
	}
	
	return CommandPhase::Error;
}

bool InputHandler::parsingPagingCommand(CommandPhase& phase, string& input) 
{
	input = InputTextUtils::toUpper(input);
	if (input == "N" || input == "NEXT") 
	{ 
		phase = CommandPhase::Next;
		return true;
	}
	if (input == "P" || input == "PREV") 
	{ 
		phase = CommandPhase::Prev;
		return true;
	}
	if (input == "Q" || input == "QUIT") 
	{ 
		phase = CommandPhase::Exit;
		return true;
	}
	if (input == "") 
	{
		phase = CommandPhase::Enter;
		return true;
	}
	return false;
}

