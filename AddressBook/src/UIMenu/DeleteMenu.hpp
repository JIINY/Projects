#pragma once
#include <string>
#include "../Common/ResultEnums.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"

class AddressBookUI;


class DeleteMenu 
{
public:
	RemoveOperationResult run(AddressBookUI& bookUI, int index, const std::string& name);


private:
	ResultVariant lastError_;
	InputHandler inputH_;
	ErrorPrintHandler errorMsgH_;
	UIPrintHandler uiMsgH_;
	UIFrame frame_;
};
