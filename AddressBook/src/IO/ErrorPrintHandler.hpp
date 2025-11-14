#pragma once
#include <string>
#include <variant>
#include <type_traits>
#include "../Common/ResultEnums.hpp"
#include "../Common/VariantUtils.hpp"



class ErrorPrintHandler 
{
public:
    void printErrorMsg(const std::variant<InputResult,
        SaveOperationResult, LoadOperationResult, AddOperationResult, RemoveOperationResult,
        MenuSelectResult, AddDataResult, AddEditResult, EditDataResult, SearchDataResult>& err);


protected:
    void setErrorMsg(const ResultVariant& err);
    void printInputErrorMsg(const InputResult err);
    void printMenuSelectErrorMsg(const MenuSelectResult err);
    void printSaveOperationErrorMsg(const SaveOperationResult err);
    void printLoadOperationErrorMsg(const LoadOperationResult err);
    void printAddOperationErrorMsg(const AddOperationResult err);
    void printAddDataErrorMsg(const AddDataResult err);
    void printAddEditErrorMsg(const AddEditResult err);
    void printEditDataErrorMsg(const EditDataResult err);

    void printSearchDataErrorMsg(const SearchDataResult err);

    void printRemoveOperationErrorMsg(const RemoveOperationResult err);


private:
    std::string errorMsg_ = "";
};

