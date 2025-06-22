#pragma once
#include "ResultEnums.hpp"
#include <string>


std::string toString(IntParsingResult value);
std::string toString(InputResult value);
std::string toString(SaveOperationResult value);
std::string toString(LoadOperationResult value);
std::string toString(AddOperationResult value);
std::string toString(RemoveOperationResult value);
std::string toString(MenuSelectResult value);
std::string toString(AddDataResult value);
std::string toString(AddEditResult value);
std::string toString(EditDataResult value);
std::string toString(SearchDataResult value);
