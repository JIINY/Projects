#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

class EditMenu
{
public:
    std::optional<PersonalData> run(AddressBookUI& bookUI, const PersonalData& dataToEdit);

protected:
    void processEditMenu(AddressBookUI& bookUI, ContextData& context);
    void processEditData(ContextData& context);
    void editDataController(ContextData& context);
    void assignEditNameEmptyError(ContextData& context);

private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
