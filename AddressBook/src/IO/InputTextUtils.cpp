#include "InputTextUtils.hpp"
#include <string>
using namespace std;


string InputTextUtils::getNegativeSub(const string& input)
{
	if (input[0] == '-')
	{
		string sub = input.substr(1);
		return sub;
	}
	return input;
}

bool InputTextUtils::isAllDigits(const string& str)
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

bool InputTextUtils::isAllZero(const string& str)
{
	for (char ch : str)
	{
		if (ch != '0') { return false; }
	}
	return true;
}

string InputTextUtils::toUpper(const string& input)
{
	string result = input;
	for (char& ch : result)
	{
		ch = toupper(static_cast<unsigned char>(ch));
	}
	return result;
}

