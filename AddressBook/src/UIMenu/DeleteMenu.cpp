#include "DeleteMenu.hpp"
#include <iostream>
#include <optional>
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
	ResultVariant result = inputH_.askYesNo();
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		string removedName;
		RemoveOperationResult deleteResult = bookUI.extractAddressBook().remove(index, removedName);

		if (deleteResult == RemoveOperationResult::SUCCESS) 
		{
		}
		else 
		{
			result = deleteResult;
			errorMsgH_.printErrorMsg(result);
		}

		inputH_.getAnyKey();
		return deleteResult;
	}

	return RemoveOperationResult::FAIL;
}

