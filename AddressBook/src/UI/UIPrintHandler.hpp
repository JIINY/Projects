#pragma once
#include <string>
#include <functional>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "UICommonData.hpp"
#include "UIOutput.hpp"

enum class CancelType;
enum class EnterType;

class UIPrintHandler
{
public:
    UIFrame menuSelect(std::optional<ResultVariant> err);
    UIFrame cancel(std::optional<ResultVariant> err, ActionType action);
    UIFrame tableAction(ActionType action);
    UIFrame short1Line();
    UIFrame short2Line();

    UIFrame mainMenu();
    UIFrame searchMenu();

    UIFrame inputName(std::optional<ResultVariant> err);
    UIFrame inputPhone();
    UIFrame inputAddress();
    UIFrame inputZipCode();
    UIFrame inputEmail();

    UIFrame addTitle();
    UIFrame addConfirm(const PersonalData& p);
    UIFrame addMenuLine(const PersonalData& p);
    UIFrame addSuccess(const int i, const PersonalData& p);
    UIFrame addAgain(std::optional<ResultVariant> err);

    UIFrame addEditTitle();
    UIFrame addEditAgain(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame addEdit(const PersonalData& p);
    UIFrame addEditLine(const PersonalData& p);

    UIFrame viewTitle(std::optional<ResultVariant> err);
    UIFrame tableDataNormal(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableDataCenter(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableDataBottom(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableSearchEnd();
    UIFrame tableComplete();
    UIFrame tableCommand();
    UIFrame tableCommandInputMessage(std::optional<ResultVariant> err);
    UIFrame tableStop(std::optional<ResultVariant> err);
    UIFrame tableEditSuccess(const int i, const std::string& name);
    UIFrame tableDeleteSuccess(const int i, const std::string& name);

    UIFrame editTitle();
    UIFrame editLongTitle();
    UIFrame personalEdit(const PersonalData& p);
    UIFrame editConfirm();
    UIFrame editName(std::optional<ResultVariant> err);
    UIFrame editPhone(std::optional<ResultVariant> err);
    UIFrame editAddress(std::optional<ResultVariant> err);
    UIFrame editZipCode(std::optional<ResultVariant> err);
    UIFrame editEmail(std::optional<ResultVariant> err);
    UIFrame editInput(std::optional<ResultVariant> err);

    UIFrame searchTitle();
    UIFrame searchLongTitle();
    UIFrame searchResult();
    UIFrame searchSubMenu(std::optional<ResultVariant> err);
    UIFrame searchEmptySubMenu(std::optional<ResultVariant> err);
    UIFrame searchEditSubMenu(std::optional<ResultVariant> err);
    UIFrame searchDeleteSubMenu(std::optional<ResultVariant> err);
    UIFrame searchActionSubMenu(std::optional<ResultVariant> err);
    UIFrame searchAgain(std::optional<ResultVariant> err);
    UIFrame searchEmpty();
    UIFrame searchEdit(std::optional<ResultVariant> err);
    UIFrame searchDelete(std::optional<ResultVariant> err);

    UIFrame deleteLongTitle();
    UIFrame deleteConfirm(std::optional<ResultVariant> err, const int i, const std::string& name);
    UIFrame deleteAllConfirm(std::optional<ResultVariant> err);
};

