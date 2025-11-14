#pragma once
#include <string>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;


class DeleteMenu 
{
public:
	RemoveOperationResult run(AddressBookUI& bookUI, int index, const std::string& name);


private:
	InputHandler inputH_{};
	ErrorPrintHandler errorMsgH_{};
	UIPrintHandler uiMsgH_{};
	UIFrame frame_{};
};

