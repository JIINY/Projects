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


enum class CancleType 
{
    Input,
    Edit,
    Delete,
    AddConfirm
};

enum class AddPhase 
{
    InputStart,
    AddMenuSelect,
    AddEditStart,
    AddEditConfirm,
    CancleConfirm,
    InputAddCancle,
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
    SearchSubMenuSelect,
    EditStart,
    EditItem,
    EditSelect,
    DeleteStart,
    DeleteItem,
    DeleteSelect,
    SearchAgain,
    Exit
};

enum class EditPhase 
{
    EditStart,
    EditItem,
    EditCancle,
    ExitSuccess,
    ExitCancel
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
