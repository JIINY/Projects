#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class ViewMenu {
public:
    void run() { processView(); }

protected:
    void processView();

private:
    ResultVariant lastError;
    InputHandler inputH;
    ErrorPrintHandler errorMsgH;
    UIPrintHandler uiMsgH;
    UIFrame frame;
    UIUtils ui;
};
