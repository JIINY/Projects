#include "DeleteMenu.hpp"
#include <iostream>
#include <utility>
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "../../UI/AddressBookUI.hpp"
using namespace std;


RemoveOperationResult DeleteMenu::run(AddressBookUI& bookUI, int index, const pair<int, string>& resultInfo)
{
	optional<ResultVariant> err = nullopt;

	//그리기
	frame_ = uiMsgH_.deleteConfirm(err, resultInfo.first, resultInfo.second);
	frame_(errorMsgH_);

	//처리
	ResultVariant result = inputH_.askYesNo();
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		string removedName;
		RemoveOperationResult deleteResult = bookUI.extractAddressBook().remove(index, removedName);

		if (deleteResult != RemoveOperationResult::SUCCESS) 
		{
			errorMsgH_.printErrorMsg(deleteResult);
		}
		return deleteResult;
	}

	return RemoveOperationResult::FAIL;
}
