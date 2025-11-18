#pragma once
#include <string>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"

class AddressBookUI;

class DeleteAllMenu
{
public:
	RemoveOperationResult run(AddressBookUI& bookUI, const std::string& filename);


private:
	InputHandler inputH_{};
	ErrorPrintHandler errorMsgH_{};
	UIPrintHandler uiMsgH_{};
	UIFrame frame_{};
};
