#include "ResultEnums.hpp"
#include <string>
using namespace std;



string toString(IntParsingResult value) 
{
    switch (value) 
    {
    case IntParsingResult::POSITIVE_NUMBER: return "IntParsing::POSITIVE_NUMBER";
    case IntParsingResult::NEGATIVE_NUMBER: return "IntParsing::NEGATIVE_NUMBER";
    case IntParsingResult::ZERO: return "IntParsing::ZERO";
    case IntParsingResult::EMPTY: return "IntParsing::EMPTY";
    case IntParsingResult::INVALID_CHAR: return "IntParsing::INVALID_CHAR";
    default: return "IntParsing::Default";
    }
}

string toString(InputResult value) 
{
    switch (value) 
    {
    case InputResult::SUCCESS: return "Input::SUCCESS";
    case InputResult::FAIL: return "Input::FAIL";
    case InputResult::WRONG_NUMBER: return "Input::WRONG_NUMBER";
    case InputResult::LENGTH_OVER: return "Input::LENGTH_OVER";
    case InputResult::EMPTY_INT: return "Input::EMPTY_INT";
    case InputResult::EMPTY_CHAR: return "Input::EMPTY_CHAR";
    case InputResult::EMPTY_STRING: return "Input::EMPTY_STRING";
    case InputResult::EMPTY_YESNO: return "Input::EMPTY_YESNO";
    case InputResult::INVALID_INT: return "Input::INVALID_INT";
    case InputResult::INVALID_CHAR: return "Input::INVALID_CHAR";
    case InputResult::INVALID_STRING: return "Input::INVALID_STRING";
    case InputResult::INVALID_YESNO: return "Input::INVALID_YESNO";
    case InputResult::UNKNOWN: return "Input::UNKNOWN";
    default: return "Input::Default";
    }
}

string toString(SaveOperationResult value) 
{
    switch (value) 
    {
    case SaveOperationResult::SUCCESS: return "SaveOperationResult::SUCCESS";
    case SaveOperationResult::FAIL: return "SaveOperationResult::Fail";
    default: return "SaveOperationResult::Default";
    }
}

string toString(LoadOperationResult value) 
{
    switch (value) 
    {
    case LoadOperationResult::SUCCESS: return "LoadOperationResult::SUCCESS";
    case LoadOperationResult::FAIL: return "LoadOperationResult::Fail";
    case LoadOperationResult::NOT_EXIST_FILE: return "LoadOperationResult::NOT_EXIST_FILE";
    default: return "LoadOperationResult::Default";
    }
}

string toString(AddOperationResult value) 
{
    switch (value) 
    {
    case AddOperationResult::SUCCESS: return "AddOperation::SUCCESS";
    case AddOperationResult::FAIL: return "AddOperation::FAIL";
    case AddOperationResult::EMPTY_NAME: return "AddOperation::EMPTY_NAME";
    case AddOperationResult::UNKNOWN: return "AddOperation::UNKNOWN";
    default: return "AddOperation::Default";
    }
}

string toString(RemoveOperationResult value) 
{
    switch (value) 
    {
    case RemoveOperationResult::SUCCESS: return "RemoveOperation::SUCCESS";
    case RemoveOperationResult::FAIL: return "RemoveOperation::FAIL";
    case RemoveOperationResult::WRONG_INDEX: return "RemoveOperation::WRONG_INDEX";
    default: return "RemoveOperation::Default";
    }
}

string toString(MenuSelectResult value) 
{
    switch (value) 
    {
    case MenuSelectResult::SUCCESS: return "MenuSelect::SUCCESS";
    case MenuSelectResult::WRONG_INDEX: return "MenuSelect::WRONG_INDEX";
    case MenuSelectResult::UNKNOWN: return "MenuSelect::UNKNOWN";
    default: return "MenuSelect::Default";
    }
}

string toString(AddDataResult value) 
{
    switch (value) 
    {
    case AddDataResult::SUCCESS: return "AddData::SUCCESS";
    case AddDataResult::EMPTY_NAME: return "AddData::EMPTY_NAME";
    case AddDataResult::UNKNOWN: return "AddData::UNKNOWN";
    default: return "AddData::Default";
    }
}

string toString(AddEditResult value) 
{
    switch (value) 
    {
    case AddEditResult::SUCCESS: return "AddEdit::SUCCESS";
    case AddEditResult::EMPTY_NAME: return "AddEdit::EMPTY_NAME";
    case AddEditResult::UNKNOWN: return "AddEdit::UNKNOWN";
    default: return "AddEdit::Default";
    }
}

string toString(EditDataResult value) 
{
    switch (value) 
    {
    case EditDataResult::SUCCESS: return "EditData::SUCCESS";
    case EditDataResult::EMPTY_NAME: return "EditData::EMPTY_NAME";
    case EditDataResult::UNKNOWN: return "EditData::UNKNOWN";
    default: return "EditData::Default";
    }
}

string toString(SearchDataResult value) 
{
    switch (value) 
    {
    case SearchDataResult::SUCCESS: return "SearchData::SUCCESS";
    case SearchDataResult::EMPTY_ITEM: return "SearchData::EMPTY_ITEM";
    case SearchDataResult::UNKNOWN: return "SearchData::UNKNOWN";
    default: return "SearchData::Default";
    }
}
