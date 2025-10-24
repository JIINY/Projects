#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class AddMenu {
public:
    void run(AddressBookUI& bookUI);


protected:
    void processAddMenu(AddressBookUI& bookUI);
    void addController(AddressBookUI& bookUI, ContextData& context);
    void addMenuController(ContextData& context);


private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
