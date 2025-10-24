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
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
