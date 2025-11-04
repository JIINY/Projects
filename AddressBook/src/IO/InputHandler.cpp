#include "InputHandler.hpp"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//Public
void InputHandler::getAnyKey() 
{
	this->lastError = getInputString(StringRule::EmptyAllow);
}

bool InputHandler::anyKeyOrQuit() 
{
	this->lastError = waitForAnyKeyOrQuit();
	return this->str == "Q";
}

int InputHandler::getInt(IntRule rule) 
{
	this->lastError = getInputNumber(rule);
	return this->num;
}
char InputHandler::getChar() 
{
	this->lastError = getInputChar();
	return this->ch;
}
string InputHandler::getString(StringRule rule) 
{
	this->lastError = getInputString(rule);
	return this->str;
}

bool InputHandler::askYesNo() 
{
	this->lastError = getInputYesNo();
	return this->yesNo;
}

ResultVariant InputHandler::getLastError() const { return this->lastError; }


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
		this->str = "";
		return InputResult::FAIL;
	}

	this->str = toUpper(input);
	return InputResult::SUCCESS;
}

ResultVariant InputHandler::getInputString(StringRule rule) 
{
	string input;
	getline(cin, input);

	if (resolveCinFailed()) 
	{
		this->str = "";
		return InputResult::FAIL;
	}

	if (input.empty()) 
	{
		this->str = "";
		if (rule == StringRule::EmptyAllow) 
		{
			return InputResult::SUCCESS;
		}
		else 
		{
			return InputResult::EMPTY_STRING;
		}
	}
	this->str = input;
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
		this->num = -1;
		return InputResult::FAIL;
	}

	IntParsingResult result = parsingInputNumber(input, num);

	if (result == IntParsingResult::INVALID_CHAR) { return InputResult::INVALID_INT; }
	if (result == IntParsingResult::EMPTY) { return InputResult::EMPTY_INT; }

	InputResult ruleResult = validateIntRule(num, rule);
	if (ruleResult != InputResult::SUCCESS) { return ruleResult; }

	this->num = num;
	return InputResult::SUCCESS;
}

ResultVariant InputHandler::getInputChar() 
{
	string input;
	getline(cin, input);
	char ch = '\0';

	if (resolveCinFailed()) 
	{
		this->ch = ch;
		return InputResult::FAIL;
	}
	
	if (input.empty()) 
	{
		this->ch = ch;
		return InputResult::EMPTY_CHAR;
	}

	if (input.length() != 1) 
	{
		this->ch = input[0];
		this->str = input;
		return InputResult::LENGTH_OVER;
	}

	if (!isalpha(input[0])) 
	{
		this->ch = ch;
		return InputResult::INVALID_CHAR;
	}

	this->ch = input[0];
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
		this->str = "";
		return InputResult::FAIL;
	}

	if (input.empty()) 
	{
		this->yesNo = false;
		return InputResult::EMPTY_CHAR;
	}

	this->str = toUpper(input);
	if (this->str == "Y" || this->str == "YES") 
	{
		this->yesNo = true;
		return InputResult::SUCCESS;
	}
	if (this->str == "N" || this->str == "NO") 
	{
		this->yesNo = false;
		return InputResult::SUCCESS;
	}

	this->yesNo = false;
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
