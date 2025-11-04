#include "SearchInputDataState.hpp"
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <cassert>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;

void SearchInputDataState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchTitle();
	frame(errorMsgH);

	switch (context.menu) {
	case 1: 
	{
		frame = uiMsgH.editName(context.err);
		frame(errorMsgH);
		break;
	}
	case 2:
	{
		frame = uiMsgH.editPhone(context.err);
		frame(errorMsgH);
		break;
	}
	case 3:
	{
		frame = uiMsgH.editAddress(context.err);
		frame(errorMsgH);
		break;
	}
	case 4:
	{
		frame = uiMsgH.editZipCode(context.err);
		frame(errorMsgH);
		break;
	}
	case 5:
	{
		frame = uiMsgH.editEmail(context.err);
		frame(errorMsgH);
		break;
	}
	default:
		break;
	}
}

SearchPhase SearchInputDataState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	auto* bookUI = owner_.getBookUI();
	auto& result = owner_.accessSearchResult();

	if (context.menu < 1 || context.menu > 5) 
	{
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
		return SearchPhase::SearchStart;
	}

	//입력 받기
	string s;
	if (context.menu == 1) 
	{
		s = inputH.getString(StringRule::EmptyDisallow);
	}
	else 
	{
		s = inputH.getString(StringRule::EmptyAllow);
	}

	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchInputData;
	}

	result.clear();
	context.err = nullopt;
	switch (context.menu) {
	case 1: 
	{
		result = bookUI->extractAddressBook().searchByName(s);
		break;
	}
	case 2:
	{
		result = bookUI->extractAddressBook().searchByPhone(s);
		break;
	}
	case 3:
	{
		result = bookUI->extractAddressBook().searchByAddress(s);
		break;
	}
	case 4:
	{
		result = bookUI->extractAddressBook().searchByZipCode(s);
		break;
	}
	case 5:
	{
		result = bookUI->extractAddressBook().searchByEmail(s);
		break;
	}
	}

	return SearchPhase::SearchResult;
}
