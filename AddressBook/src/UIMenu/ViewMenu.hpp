#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class ViewMenu
{
public:
    void run(AddressBookUI& bookUI) { processView(bookUI); }


private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;

    void processView(AddressBookUI& bookUI);
    void drawPage(AddressBookUI& bookUI, ContextData& context, int page, int length);
    bool handlePageInput(ContextData& context, int page, int length);
};
