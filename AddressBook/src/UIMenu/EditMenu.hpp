#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class EditMenu
{
public:
    std::optional<PersonalData> run(AddressBookUI& bookUI, const PersonalData& dataToEdit);


private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;

    EditPhase onEditStart(ContextData& context);
    EditPhase onEditItem(ContextData& context);
    EditPhase onEditCancle(ContextData& context);
    void processEditData(ContextData& context);

};
