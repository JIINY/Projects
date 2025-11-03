#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;
enum class ViewPhase { Next, Stay, Exit };

class ViewMenu
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

    void draw(AddressBookUI& bookUI, ContextData& context, int page, int length);
    ViewPhase update(ContextData& context, int page, int length);
};
