#include "DeleteAllMenu.hpp"
#include <iostream>
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "../../UI/AddressBookUI.hpp"
using namespace std;


RemoveOperationResult DeleteAllMenu::run(AddressBookUI& bookUI, const string& filename)
{
	optional<ResultVariant> err = nullopt;

	//그리기
	frame_ = uiMsgH_.deleteAllConfirm(err);
	frame_(errorMsgH_);

	//처리
	ResultVariant result = inputH_.askYesNo();
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		RemoveOperationResult deleteResult = bookUI.extractAddressBook().removeAll(filename);
		if (deleteResult != RemoveOperationResult::SUCCESS)
		{
			errorMsgH_.printErrorMsg(deleteResult);
		}
		return deleteResult;
	}

	return RemoveOperationResult::FAIL;
}
