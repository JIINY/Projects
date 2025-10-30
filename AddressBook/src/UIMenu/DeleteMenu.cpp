#include "DeleteMenu.hpp"
#include <iostream>
#include <optional>
#include "../Common/VariantUtils.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
using namespace std;


RemoveOperationResult DeleteMenu::run(AddressBookUI& bookUI, int index, const string& name) 
{
	optional<ResultVariant> err = nullopt;

	//그리기
	frame_ = uiMsgH_.deleteConfirm(err, index + 1, name);
	frame_(errorMsgH_);

	//처리
	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		return RemoveOperationResult::FAIL;
	}

	if (yesNo) 
	{
		string removedName;
		RemoveOperationResult deleteResult = bookUI.extractAddressBook().remove(index, removedName);

		if (deleteResult == RemoveOperationResult::SUCCESS) 
		{
		}
		else 
		{
			lastError_ = deleteResult;
			errorMsgH_.printErrorMsg(lastError_);
		}

		inputH_.getAnyKey();
		return deleteResult;
	}
	else 
	{
		return RemoveOperationResult::FAIL;
	}
}
