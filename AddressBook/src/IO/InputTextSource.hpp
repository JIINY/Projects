#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <limits>


class InputTextSource 
{
public:
	std::pair<bool, std::string> readTextSource() 
	{
		std::string input;
		std::getline(std::cin, input);

		if (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return { false, "" };
		}

		return { true, input };
	}
};

