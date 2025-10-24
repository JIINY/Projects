#pragma once
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;

enum class MainMenuResult
{
    Add,
    View,
    Search,
    Exit
};


class MainMenu
{
public:
    void run(AddressBookUI& bookUI);
    ResultVariant getLastError() const;

protected:
    void processMainMenu(AddressBookUI& bookUI);
    ResultVariant mainMenuController(AddressBookUI& bookUI, int input);

private:
    ResultVariant lastError_;
    InputHandler inputH_;
    ErrorPrintHandler errorMsgH_;
    UIPrintHandler uiMsgH_;
    UIFrame frame_;
    UIUtils ui_;
};
