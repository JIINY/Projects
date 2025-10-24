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

protected:
    void processSearchMenu(AddressBookUI& bookUI);
    void searchMenuController(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    ResultVariant processSearchItem(ContextData& context);
    void searchItemController(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    void printSearchResultTable(ContextData& context, std::vector<std::pair<PersonalData, int>> result);

    ResultVariant processSearchSubMenu(ContextData& context);
    ResultVariant processSearchEmptySubMenu(ContextData& context);
    void searchSubMenuController(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& result);
    void processEditItem(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& searchResult);
    void processDeleteItem(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& searchResult);

private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
