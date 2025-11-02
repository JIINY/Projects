#pragma once
#include <variant>
#include <optional>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "AddressBookUI.hpp"


struct PersonalPrintFormat 
{
    int no, name, phone, address, zipCode, email;
};
constexpr PersonalPrintFormat f = { 6, 12, 18, 40, 10, 25 };

enum class InputMode 
{ 
    Add, 
    AddEdit, 
    Edit 
};

enum class CancelType 
{
    Input,
    Edit,
    Delete,
    AddConfirm
};

enum class AddPhase 
{
    AddInputStart,
    AddReview,
    AddEditStart,
    AddEditConfirm,
    CancelConfirm,
    AskAddCancel,
    AddSuccess,
    AddAgain,
    Exit
};

enum class SearchPhase 
{
    SearchStart,
    SearchMenuSelect,
    SearchResultPrint,
    SearchNextStart,
    EditStart,
    EditItem,
    EditAgain,
    DeleteStart,
    DeleteItem,
    DeleteAgain,
    SearchAgain,
    Exit
};

enum class EditPhase 
{
    EditStart,
    EditItem,
    EditCancel,
    ExitSuccess,
    ExitCancel
};

enum class DataInputPhase 
{
    InputName,
    InputPhone,
    InputAddress,
    InputZipCode,
    InputEmail,
    Exit
};

using PhaseVariant = std::variant<AddPhase, EditPhase, SearchPhase>;

struct ContextData 
{
    PhaseVariant phase;
    PersonalData p;
    PersonalData sub;

    std::optional<ResultVariant> err = std::nullopt;
    int menu = -1;
};
