#pragma once
#include <memory>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "IViewState.hpp"

class AddressBookUI;

class ViewMenu
{
public:
    void run(AddressBookUI& bookUI);

    ContextData& getContext() { return context_; }
    int& getPage() { return page_; }
    InputHandler& getInputH() { return inputH_; }
    ErrorPrintHandler& getErrorMsgH() { return errorMsgH_; }
    UIPrintHandler& getUIMsgH() { return uiMsgH_; }
    UIFrame& getUIFrame() { return frame_; }
    UIUtils& getUI() { return ui_; }

    AddressBookUI* getBookUI() const { return bookUI_; }
    int getLength() const;

    //void setPhase(ViewPhase phase) { currentPhase_ = phase; }

private:
    InputHandler inputH_{};
    ErrorPrintHandler errorMsgH_{};
    UIPrintHandler uiMsgH_{};
    UIFrame frame_{};
    UIUtils ui_{};

    AddressBookUI* bookUI_ = nullptr;
    ContextData context_{};
    int page_ = 0;
    std::unique_ptr<IViewState> currentState_ = nullptr;

    bool transitionTo(ViewPhase nextPhase);
};
