#include "SearchMenu.hpp"
#include <vector>
#include <optional>
#include <algorithm>
#include <utility>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
#include "EditMenu.hpp"
#include "DeleteMenu.hpp"
using namespace std;


void SearchMenu::run(AddressBookUI& bookUI)
{
	ContextData context;
	SearchPhase currentPhase = SearchPhase::SearchStart;
	vector<pair<PersonalData, int>> result;
	context.err = nullopt;

	while (currentPhase != SearchPhase::Exit)
	{
		//그리기
		switch (currentPhase){
		case (SearchPhase::SearchStart):
		{
			frame_ = uiMsgH_.searchMenu();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			break;
		}
		case(SearchPhase::SearchResultPrint):
		{
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);

			printSearchResultTable(context, result);
			break;
		}
		case(SearchPhase::SearchNextStart):
		{
			int length = static_cast<int>(result.size());
			if (length == 0)
			{
				frame_ = uiMsgH_.searchEmptySubMenu();
			}
			else
			{
				frame_ = uiMsgH_.searchSubMenu();
			}
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			break;
		}
		case(SearchPhase::EditStart):
		{
			frame_ = uiMsgH_.searchEdit(context.err);
			frame_(errorMsgH_);
			break;
		}
		case(SearchPhase::DeleteStart):
		{
			frame_ = uiMsgH_.searchDelete(context.err);
			frame_(errorMsgH_);
			break;
		}
		default:
			break;
		}


		//처리
		SearchPhase nextPhase = currentPhase;
		switch (currentPhase) {
		case SearchPhase::SearchStart:
		{
			nextPhase = onSearchStart(context);
			break;
		}
		case SearchPhase::SearchMenuSelect:
		{
			nextPhase = onSearchMenuSelect(bookUI, context, result);
			break;
		}
		case SearchPhase::SearchResultPrint:
		{
			nextPhase = SearchPhase::SearchNextStart;
			break;
		}
		case SearchPhase::SearchNextStart:
		{
			nextPhase = onSearchNextStart(context, result);
			break;
		}
		case SearchPhase::SearchSubMenuSelect:
		{
			nextPhase = onSearchSubMenuSelect(context, result);
			break;
		}
		case SearchPhase::EditStart:
		{
			nextPhase = onEditStart(context, result);
			break;
		}
		case SearchPhase::EditItem: 
		{
			nextPhase = onEditItem(bookUI, context, result);
			break;
		}
		case SearchPhase::DeleteStart: 
		{
			nextPhase = onDeleteStart(context, result);
			break;
		}
		case SearchPhase::DeleteItem:
		{
			nextPhase = onDeleteItem(bookUI, context, result);
			break;
		}
		case SearchPhase::SearchAgain:
		{
			nextPhase = onSearchAgain(context);
			break;
		}
		case SearchPhase::Exit:
			break;
		default:
			break;
		}

		//화면 정리 및 상태 전이
		if (currentPhase != SearchPhase::SearchMenuSelect && currentPhase != SearchPhase::EditItem && currentPhase != SearchPhase::DeleteItem) 
		{
			ui_.clearScreen();
		}
		currentPhase = nextPhase;
	}
}

SearchPhase SearchMenu::onSearchStart(ContextData& context) 
{
	context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchStart;
	}

	context.err = nullopt;
	if (context.menu == 0) 
	{
		return SearchPhase::Exit;
	}
	return SearchPhase::SearchMenuSelect;
}

SearchPhase SearchMenu::onSearchMenuSelect(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result)
{
	//검색어 그리기
	lastError_ = processSearchItem(context);
	if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchStart;
	}


	//입력받기
	string input;
	if (context.menu == 1) 
	{
		input = inputH_.getString(StringRule::EmptyDisallow);
	}
	else 
	{
		input = inputH_.getString(StringRule::EmptyAllow);
	}

	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchStart;
	}


	//검색 실행
	result.clear();
	context.err = nullopt;
	switch (context.menu) {
	case 1: 
	{
		result = bookUI.extractAddressBook().searchByName(input);
		break;
	}
	case 2: 
	{
		result = bookUI.extractAddressBook().searchByPhone(input);
		break;
	}
	case 3: 
	{
		result = bookUI.extractAddressBook().searchByAddress(input);
		break;
	}
	case 4: 
	{
		result = bookUI.extractAddressBook().searchByZipCode(input);
		break;
	}
	case 5:
	{
		result = bookUI.extractAddressBook().searchByEmail(input);
		break;
	}
	}

	return SearchPhase::SearchResultPrint;
}

SearchPhase SearchMenu::onSearchNextStart(ContextData& context, const  vector<pair<PersonalData, int>>& result) 
{
	context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	context.err = nullopt;
	return SearchPhase::SearchSubMenuSelect;
}

SearchPhase SearchMenu::onSearchSubMenuSelect(ContextData& context, const vector<pair<PersonalData, int>>& result)
{
	int length = static_cast<int>(result.size());
	if (length == 0)
	{
		lastError_ = processSearchEmptySubMenu(context);
	}
	else
	{
		lastError_ = processSearchSubMenu(context);
	}

	if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}


	switch (context.menu) {
	case 1: return SearchPhase::EditStart;
	case 2: return SearchPhase::DeleteStart;
	case 9: return SearchPhase::SearchAgain;
	case 0: return SearchPhase::Exit;
	default: return SearchPhase::SearchNextStart;
	}
}

SearchPhase SearchMenu::onEditStart(ContextData& context, const vector<pair<PersonalData, int>>& result) 
{
	int input = inputH_.getInt(IntRule::PositiveOnly);
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	int resultCount = static_cast<int>(result.size());
	if (input > resultCount || input <= 0) 
	{
		lastError_ = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	context.menu = input - 1;
	context.err = nullopt;
	return SearchPhase::EditItem;
}

SearchPhase SearchMenu::onEditItem(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result)
{
	int i = context.menu;
	PersonalData dataToEdit = result[i].first;
	int index = result[i].second;

	EditMenu editMenu;
	optional<PersonalData> editResult = editMenu.run(bookUI, dataToEdit);

	if (editResult.has_value())
	{
		PersonalData editedData = editResult.value();
		AddOperationResult addResult = bookUI.extractAddressBook().edit(index, editedData);
		
		if (addResult == AddOperationResult::SUCCESS) 
		{
			frame_ = uiMsgH_.editSuccess(i + 1, editedData.name);
			frame_(errorMsgH_);
			inputH_.getAnyKey();
		}
		else 
		{
			lastError_ = addResult;
			context.err = wrapVariant<ResultVariant>(lastError_);
			errorMsgH_.printErrorMsg(lastError_);
			inputH_.getAnyKey();
		}
	}
	return SearchPhase::SearchStart;
}

SearchPhase SearchMenu::onDeleteStart(ContextData& context, const vector<pair<PersonalData, int>>& result) 
{
	int input = inputH_.getInt(IntRule::PositiveOnly);
	lastError_ = inputH_.getLastError();

	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	int resultCount = static_cast<int>(result.size());
	if (input > resultCount || input <= 0) 
	{
		lastError_ = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	context.menu = input - 1;
	context.err = nullopt;
	return SearchPhase::DeleteItem;
}

SearchPhase SearchMenu::onDeleteItem(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result) 
{
	int i = context.menu;
	string name = result[i].first.name;
	int index = result[i].second;

	DeleteMenu deleteMenu;
	deleteMenu.run(bookUI, index, name);

	return SearchPhase::SearchStart;
}

SearchPhase SearchMenu::onSearchAgain(ContextData& context) 
{
	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		return SearchPhase::SearchNextStart;
	}

	if (yesNo) 
	{
		context.err = nullopt;
		return SearchPhase::SearchStart;
	}
	context.err = nullopt;
	return SearchPhase::SearchNextStart;
}

void SearchMenu::printSearchResultTable(ContextData& context, vector<pair<PersonalData, int>> result)
{
	int page = 0;

	int length = static_cast<int>(result.size());
	if (length == 0)
	{
		frame_ = uiMsgH_.searchEmpty();
		frame_(errorMsgH_);
	}
	else {
		for (int i = page; i < length && i < page + 10; i++)
		{
			context.p = result[i].first;
			context.sub = ui_.getPersonalDataTableFormat(context.p);

			int remainder = (i + 1) % 10;
			if (remainder == 5)
			{
				frame_ = uiMsgH_.tableDataCenter(context.err, i + 1, context.sub);
			}
			else if (remainder == 0 || (i + 1) == length)
			{
				frame_ = uiMsgH_.tableDataBottom(context.err, i + 1, context.sub);
				frame_(errorMsgH_);

				if (i + 1 == length) 
				{
					frame_ = uiMsgH_.tableSearchEnd(context.err);
				}
				else
				{
					frame_ = uiMsgH_.tableContinue(context.err);
				}
			}
			else
			{
				frame_ = uiMsgH_.tableDataNormal(context.err, i + 1, context.sub);
			}
			frame_(errorMsgH_);
		}
	}
}

ResultVariant SearchMenu::processSearchItem(ContextData& context)
{
	UIUtils::clearScreen();
	frame_ = uiMsgH_.searchTitle();
	frame_(errorMsgH_);

	switch (context.menu)
	{
	case 1:
	{
		frame_ = uiMsgH_.editName(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 2:
	{
		frame_ = uiMsgH_.editPhone(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 3:
	{
		frame_ = uiMsgH_.editAddress(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 4:
	{
		frame_ = uiMsgH_.editZipCode(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 5:
	{
		frame_ = uiMsgH_.editEmail(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default:
		return MenuSelectResult::WRONG_INDEX;
	}
}

ResultVariant SearchMenu::processSearchSubMenu(ContextData& context)
{
	switch (context.menu)
	{
	case(1):
	{
		frame_ = uiMsgH_.searchEdit(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case(2):
	{
		frame_ = uiMsgH_.searchDelete(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case(9):
	{
		frame_ = uiMsgH_.searchAgain(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default:
	{
		return MenuSelectResult::WRONG_INDEX;
	}
	}
}

ResultVariant SearchMenu::processSearchEmptySubMenu(ContextData& context)
{
	switch (context.menu)
	{
	case(9):
	{
		frame_ = uiMsgH_.searchAgain(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default:
	{
		return MenuSelectResult::WRONG_INDEX;
	}
	}
}
