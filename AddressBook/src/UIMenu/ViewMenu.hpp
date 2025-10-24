#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class ViewMenu
{
public:
    void run(AddressBookUI& bookUI) { processView(bookUI); }

protected:
    void processView(AddressBookUI& bookUI);

private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
