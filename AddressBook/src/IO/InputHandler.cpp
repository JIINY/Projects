#include "InputHandler.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <cctype>
using namespace std;

//Public
void InputHandler::getAnyKey() 
{
	this->lastError_ = getInputString(StringRule::EmptyAllow);
}

bool InputHandler::anyKeyOrQuit() 
{
	this->lastError_ = waitForAnyKeyOrQuit();
	return this->str_ == "Q";
}

int InputHandler::getInt(IntRule rule) 
{
	this->lastError_ = getInputNumber(rule);
	return this->num_;
}
char InputHandler::getChar() 
{
	this->lastError_ = getInputChar();
	return this->ch_;
}
string InputHandler::getString(StringRule rule) 
{
	this->lastError_ = getInputString(rule);
	return this->str_;
}

bool InputHandler::askYesNo() 
{
	this->lastError_ = getInputYesNo();
	return this->yesNo_;
}

PagingPhase InputHandler::getPagingInput(PagingMenu menu) 
{
	this->lastError_ = getInputString(StringRule::EmptyAllow);
	if (!isVariantEqualTo<InputResult>(this->lastError_, InputResult::SUCCESS))
	{
		return PagingPhase::Error;
	}

	string input = toUpper(this->str_);
	if (input == "N") { return PagingPhase::Next; }
	if (input == "P") { return PagingPhase::Prev; }
	if (input == "Q") { return PagingPhase::Exit; }

	if (menu == PagingMenu::View) 
	{
		return PagingPhase::Stay;
	}
	else 
	{
		if (this->str_.empty()) 
		{
			return PagingPhase::Enter;
		}

		int parsed = -1;
		IntParsingResult result = parsingInputNumber(this->str_, parsed);

		if (result == IntParsingResult::POSITIVE_NUMBER) 
		{
			this->num_ = parsed;
			return PagingPhase::PositiveNums;
		}
	}

	this->lastError_ = wrapVariant<ResultVariant>(InputResult::INVALID_INT);
	return PagingPhase::Error;
}


string InputHandler::getNegativeSub(const string& input) 
{
	if (input[0] == '-') 
	{
		string sub = input.substr(1);
		return sub;
	}
	return input;
}

bool InputHandler::isAllDigits(const string& str) 
{
	for (char ch : str)
	{
		if (isdigit(static_cast<unsigned char>(ch)) == 0) //숫자가 아니면 0 반환
		{
			return false;
		}
	}
	return true;
}

bool InputHandler::isAllZero(const string& str) 
{
	for (char ch : str)
	{
		if (ch != '0') { return false; }
	}
	return true;
}

IntParsingResult InputHandler::parsingInputNumber(const string& input, int& output) 
{
	int convertNum = atoi(input.c_str());

	string numCheck = getNegativeSub(input);
	bool isInputNumber = isAllDigits(numCheck);

	if (input.empty()) 
	{
		output = -1;
		return IntParsingResult::EMPTY;
	}
	if (input[0] == '-' && isInputNumber) 
	{ 
		output = convertNum;
		return IntParsingResult::NEGATIVE_NUMBER;
	}
	if (isAllZero(input)) 
	{
		output = 0;
		return IntParsingResult::ZERO;
	}
	if (!isInputNumber) 
	{
		output = -1;
		return IntParsingResult::INVALID_CHAR; 
	}
	output = convertNum;
	return IntParsingResult::POSITIVE_NUMBER;
}

ResultVariant InputHandler::waitForAnyKeyOrQuit() 
{
	string input;
	getline(cin, input);

	if (resolveCinFailed()) 
	{
		this->str_ = "";
		return InputResult::FAIL;
	}

	this->str_ = toUpper(input);
	return InputResult::SUCCESS;
}

ResultVariant InputHandler::getInputString(StringRule rule) 
{
	string input;
	getline(cin, input);

	if (resolveCinFailed()) 
	{
		this->str_ = "";
		return InputResult::FAIL;
	}

	if (input.empty()) 
	{
		this->str_ = "";
		if (rule == StringRule::EmptyAllow) 
		{
			return InputResult::SUCCESS;
		}
		else 
		{
			return InputResult::EMPTY_STRING;
		}
	}
	this->str_ = input;
	return InputResult::SUCCESS;
}

InputResult InputHandler::validateIntRule(int i, IntRule rule) 
{
	switch (rule) 
	{
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

ResultVariant InputHandler::getInputNumber(IntRule rule) 
{
	string input;
	getline(cin, input); //파싱하기 위해 일단 string으로 입력
	int num = -1;

	if (resolveCinFailed()) 
	{
		this->num_ = -1;
		return InputResult::FAIL;
	}

	IntParsingResult result = parsingInputNumber(input, num);

	if (result == IntParsingResult::INVALID_CHAR) { return InputResult::INVALID_INT; }
	if (result == IntParsingResult::EMPTY) { return InputResult::EMPTY_INT; }

	InputResult ruleResult = validateIntRule(num, rule);
	if (ruleResult != InputResult::SUCCESS) { return ruleResult; }

	this->num_ = num;
	return InputResult::SUCCESS;
}

ResultVariant InputHandler::getInputChar() 
{
	string input;
	getline(cin, input);
	char ch = '\0';

	if (resolveCinFailed()) 
	{
		this->ch_ = ch;
		return InputResult::FAIL;
	}
	
	if (input.empty()) 
	{
		this->ch_ = ch;
		return InputResult::EMPTY_CHAR;
	}

	if (input.length() != 1) 
	{
		this->ch_ = input[0];
		this->str_ = input;
		return InputResult::LENGTH_OVER;
	}

	if (!isalpha(input[0])) 
	{
		this->ch_ = ch;
		return InputResult::INVALID_CHAR;
	}

	this->ch_ = input[0];
	return InputResult::SUCCESS;
}

string InputHandler::toUpper(const string& input) 
{
	string result = input;
	for (char& ch : result) 
	{
		ch = toupper(static_cast<unsigned char>(ch));
	}
	return result;
}

ResultVariant InputHandler::getInputYesNo() 
{
	string input;
	getline(cin, input);

	if (resolveCinFailed()) 
	{
		this->str_ = "";
		return InputResult::FAIL;
	}

	if (input.empty()) 
	{
		this->yesNo_ = false;
		return InputResult::EMPTY_CHAR;
	}

	this->str_ = toUpper(input);
	if (this->str_ == "Y" || this->str_ == "YES")
	{
		this->yesNo_ = true;
		return InputResult::SUCCESS;
	}
	if (this->str_ == "N" || this->str_ == "NO")
	{
		this->yesNo_ = false;
		return InputResult::SUCCESS;
	}

	this->yesNo_ = false;
	return InputResult::INVALID_YESNO;
}

bool InputHandler::resolveCinFailed() 
{
	if (cin.fail()) 
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	return false;
}
