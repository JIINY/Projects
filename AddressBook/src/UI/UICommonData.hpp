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
    InputAddCancle,
    InputAddMenu,
    AddSuccess,
    AddAgain,
    AddEditStart,
    AddEditSelect,
    AddEditMenu,
    AddEditConfirm,
    AddEditAgain,
    CancleConfirm,
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

enum class EditPhase {
    EditStart
};

using PhaseVariant = std::variant<AddPhase, EditPhase, SearchPhase>;

enum class EditDataCaller {
    AddEdit,
    Edit
};
struct ContextData 
{
    PhaseVariant phase;
    PersonalData p;
    PersonalData sub;
    EditDataCaller caller = EditDataCaller::AddEdit;

    std::optional<ResultVariant> err = std::nullopt;
    int menu = -1;
};
