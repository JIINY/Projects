#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"


class EditMenu {
public:
    void editMenuPhaseController(ContextData& context);

protected:
    void processAddEditMenu(ContextData& context);
    void addEditController(ContextData& context);
    void processEditData(ContextData& context);
    void editDataController(ContextData& context);
    void processEditMenu(ContextData& context);
    void assignEditNameEmptyError(ContextData& context);

private:
    ResultVariant lastError;
    InputHandler inputH;
    ErrorPrintHandler errorMsgH;
    UIPrintHandler uiMsgH;
    UIFrame frame;
    UIUtils ui;
};
