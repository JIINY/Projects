#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

enum class MainMenuResult {
    Add,
    View,
    Search,
    Exit
};


class MainMenu {
public:
    void run();
    ResultVariant getLastError() const;

protected:
    void processMainMenu();
    ResultVariant mainMenuController(int input);

private:
    ResultVariant lastError;
    InputHandler inputH;
    ErrorPrintHandler errorMsgH;
    UIPrintHandler uiMsgH;
    UIFrame frame;
    UIUtils ui;
};
