#pragma once
#include <optional>
#include <memory>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "States/IAddState.hpp"

class AddressBookUI;

class AddMenu
{
public:
    void run(AddressBookUI& bookUI);

    ContextData& getContext() { return context_; }
    AddressBookUI* getAddressBookUI() { return bookUI_; }
    InputHandler& getInputH() { return inputH_; }
    ErrorPrintHandler& getErrorMsgH() { return errorMsgH_; }
    UIPrintHandler& getUIMsgH() { return uiMsgH_; }
    UIFrame& getUIFrame() { return frame_; }
    UIUtils& getUI() { return ui_; }


private:
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;

    AddressBookUI* bookUI_ = nullptr;
    ContextData context_{};
    std::unique_ptr<IAddState> currentState_ = nullptr;

    void transitionTo(AddPhase nextPhase);
};
