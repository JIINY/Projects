#pragma once
#include <optional>
#include <memory>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "IEditState.hpp"

class AddressBookUI;

class EditMenu
{
public:
    EditMenu(InputMode mode) : mode_(mode) {}

    std::optional<PersonalData> run(AddressBookUI& bookUI, const PersonalData& dataToEdit);
    InputMode getMode() { return mode_; }

    ContextData& getContext() { return context_; }
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
    InputMode mode_;

    AddressBookUI* bookUI_ = nullptr;
    ContextData context_{};
    std::unique_ptr<IEditState> currentState_ = nullptr;

    void transitionTo(EditPhase nextPhase);
};
