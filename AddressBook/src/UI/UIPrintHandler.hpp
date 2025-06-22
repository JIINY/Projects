#pragma once
#include <string>
#include <functional>
#include "../Common/DataType.hpp"
#include "../Common/ResultEnums.hpp"
#include "UIOutput.hpp"

enum class CancleType;
enum class EnterType;

class UIPrintHandler {
public:
    UIFrame menuSelect(std::optional<ResultVariant> err);
    UIFrame cancle(std::optional<ResultVariant> err, CancleType action);
    UIFrame short1Line();
    UIFrame short2Line();

    UIFrame mainMenu();
    UIFrame searchMenu();

    UIFrame inputName(std::optional<ResultVariant> err);
    UIFrame inputPhone();
    UIFrame inputAddress();
    UIFrame inputZipCode();
    UIFrame inputEmail();

    UIFrame addConfirm(const PersonalData& p);
    UIFrame addMenuLine(const PersonalData& p);
    UIFrame addSuccess(const int i, const PersonalData& p);
    UIFrame addAgain(std::optional<ResultVariant> err);

    UIFrame addEditAgain(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame addEdit(const PersonalData& p);
    UIFrame addEditLine(const PersonalData& p);

    UIFrame viewTitle(std::optional<ResultVariant> err);
    UIFrame tableDataNormal(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableDataCenter(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableDataBottom(std::optional<ResultVariant> err, const int i, const PersonalData& p);
    UIFrame tableSearchEnd(std::optional<ResultVariant> err);
    UIFrame tableComplete(std::optional<ResultVariant> err);
    UIFrame tableContinue(std::optional<ResultVariant> err);
    UIFrame tableStop(std::optional<ResultVariant> err);

    UIFrame editName(std::optional<ResultVariant> err);
    UIFrame editPhone(std::optional<ResultVariant> err);
    UIFrame editAddress(std::optional<ResultVariant> err);
    UIFrame editZipCode(std::optional<ResultVariant> err);
    UIFrame editEmail(std::optional<ResultVariant> err);
    UIFrame editInput(std::optional<ResultVariant> err);

    UIFrame searchTitle();
    UIFrame searchResult();
    UIFrame searchSubMenu();
    UIFrame searchEmptySubMenu();
    UIFrame searchEdit(std::optional<ResultVariant> err);
    UIFrame searchDelete(std::optional<ResultVariant> err);
    UIFrame searchAgain(std::optional<ResultVariant> err);
    UIFrame searchEmpty();
};
