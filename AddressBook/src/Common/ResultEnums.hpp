#pragma once
#include <variant>


//InputHandler
enum class InputResult 
{
    SUCCESS, 
    FAIL,
    YES,
    NO,
    WRONG_NUMBER, 
    LENGTH_OVER,
    EMPTY_INT, 
    EMPTY_CHAR, 
    EMPTY_STRING, 
    EMPTY_YESNO,    
    INVALID_INT, 
    INVALID_CHAR, 
    INVALID_STRING, 
    INVALID_YESNO,
    UNKNOWN
};



//AddressBook
enum class SaveOperationResult 
{
    SUCCESS,
    FAIL
};

enum class LoadOperationResult 
{
    SUCCESS,
    FAIL,
    NOT_EXIST_FILE,
    EMPTY_FILE
};

enum class AddOperationResult 
{
    SUCCESS,
    FAIL,
    EMPTY_NAME,
    UNKNOWN
};

enum class RemoveOperationResult 
{
    SUCCESS,
    FAIL,
    NOT_FOUND,
    FILE_DELETE_FAILED,
    WRONG_INDEX
};



//AddressBookUI
enum class MenuSelectResult 
{
    SUCCESS,
    WRONG_INDEX,
    EMPTY_ADDRESSBOOK,
    WRONG_COMMAND,
    PAGE_START,
    PAGE_END,
    UNKNOWN
};

enum class AddDataResult 
{
    SUCCESS,
    EMPTY_NAME,
    UNKNOWN
};

enum class AddEditResult 
{
    SUCCESS,
    EMPTY_NAME,
    UNKNOWN
};

enum class EditDataResult 
{
    SUCCESS,
    EMPTY_NAME,
    UNKNOWN
};

enum class SearchDataResult 
{
    SUCCESS,
    EMPTY_ITEM,
    UNKNOWN
};


using ResultVariant = std::variant<InputResult, 
    SaveOperationResult, LoadOperationResult, AddOperationResult, RemoveOperationResult, 
    MenuSelectResult, AddDataResult, AddEditResult, EditDataResult, SearchDataResult>;

