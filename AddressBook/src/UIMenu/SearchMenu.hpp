#pragma once
#include <vector>
#include <utility>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class SearchMenu {
public:
    void run();

protected:
    void processSearchMenu();
    void searchMenuController(ContextData& context, std::vector<pair<PersonalData, int>>& result);
    ResultVariant processSearchItem(ContextData& context);
    void searchItemController(ContextData& context, std::vector<pair<PersonalData, int>>& result);
    void printSearchResultTable(ContextData& context, vector<pair<PersonalData, int>> result);

    ResultVariant processSearchSubMenu(ContextData& context);
    ResultVariant processSearchEmptySubMenu(ContextData& context);
    void searchSubMenuController(ContextData& context);


private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
