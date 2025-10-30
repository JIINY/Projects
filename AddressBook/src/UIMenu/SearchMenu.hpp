#pragma once
#include <vector>
#include <utility>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUi;

class SearchMenu
{
public:
    void run(AddressBookUI& bookUI);


private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;

    SearchPhase onSearchStart(ContextData& context);
    SearchPhase onSearchMenuSelect(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onSearchNextStart(ContextData& context, const std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onEditStart(ContextData& context, const std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onEditItem(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onDeleteStart(ContextData& context, const std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onDeleteItem(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    SearchPhase onSearchAgain(ContextData& context);

    void printSearchResultTable(ContextData& context, std::vector<std::pair<PersonalData, int>> result);
    void printSearchTitle();
    ResultVariant processSearchItem(ContextData& context);
    ResultVariant processSearchSubMenu(ContextData& context);
    ResultVariant processSearchEmptySubMenu(ContextData& context);
};
