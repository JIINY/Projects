#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class AddMenu
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

    AddPhase onInputStart(ContextData& context);
    AddPhase onAddMenuSelect(ContextData& context);
    AddPhase onInputAddCancel(ContextData& context);
    AddPhase onAddSuccess(AddressBookUI& bookUI, ContextData& context);
    AddPhase onAddAgain(ContextData& context);
    AddPhase onAddEditStart(AddressBookUI& bookUI, ContextData& context);
    AddPhase onAddEditConfirm(AddressBookUI& bookUI, ContextData& context);
    AddPhase processMenuSelection(ContextData& context);
};
