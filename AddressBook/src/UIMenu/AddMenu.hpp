#pragma once
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"



class AddMenu {
public:
    void run();


protected:
    void processAddMenu();
    void addController(ContextData& context);
    void addMenuController(ContextData& context);


private:
    ResultVariant lastError;
    InputHandler inputH;
    ErrorPrintHandler errorMsgH;
    UIPrintHandler uiMsgH;
    UIFrame frame;
    UIUtils ui;
};
