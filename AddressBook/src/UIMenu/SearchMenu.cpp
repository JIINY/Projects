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
using namespace std;


void SearchMenu::run(AddressBookUI& bookUI)
{
	processSearchMenu(bookUI);
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

void SearchMenu::processSearchMenu(AddressBookUI& bookUI)
{
	ContextData context;
	context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchStart);
	vector<pair<PersonalData, int>> result;

	while (true)
	{
		SearchPhase phase = unwrapVariant<SearchPhase>(context.phase);
		switch (phase)
		{
		case (SearchPhase::SearchStart):
		{
			frame_ = uiMsgH_.searchMenu();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			searchMenuController(bookUI, context, result);
			break;
		}
		case(SearchPhase::SearchMenuSelect):
		{
			if (context.menu == 0)
			{
				context.phase = wrapVariant<PhaseVariant>(SearchPhase::Exit);
				break; 
			}

			frame_ = uiMsgH_.searchMenu();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			searchMenuController(bookUI, context, result);
			break;
		}
		case(SearchPhase::SearchResultPrint):
		{
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);

			printSearchResultTable(context, result);
			searchMenuController(bookUI, context, result);
			break;
		}
		case(SearchPhase::SearchNextStart):
		{
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);
			printSearchResultTable(context, result);

			int length = static_cast<int>(result.size());
			if (length == 0)
			{
				frame_ = uiMsgH_.searchEmptySubMenu();
				frame_(errorMsgH_);
			}
			else
			{
				frame_ = uiMsgH_.searchSubMenu();
				frame_(errorMsgH_);
			}
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);

			searchMenuController(bookUI, context, result);
			continue;
		}
		case(SearchPhase::SearchSubMenuSelect):
		{
			searchMenuController(bookUI, context, result);
			
			if (context.menu == 9) { break; }
			break;
		}
		case(SearchPhase::EditStart):
		{
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);
			printSearchResultTable(context, result);

			frame_ = uiMsgH_.searchEdit(context.err);
			frame_(errorMsgH_);

			searchMenuController(bookUI, context, result);
			break;
		}
		case(SearchPhase::EditItem):
		{
			searchMenuController(bookUI, context, result);
			continue;
		}
		case(SearchPhase::DeleteStart):
		{
			//frame = uiMsgH.selectItem();
			//frame(errorMsgH);
			searchMenuController(bookUI, context, result);
			break;
		}
		}

		ui_.clearScreen();
		if (phase == SearchPhase::Exit) {
			break;
		}
	}
}

void SearchMenu::searchMenuController(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result)
{
	SearchPhase phase = unwrapVariant<SearchPhase>(context.phase);
	switch (phase)
	{
	case(SearchPhase::SearchStart):
	{
		context.menu = inputH_.getInt(IntRule::ZeroOrPositive);

		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
		{
			context.err = wrapVariant<ResultVariant>(lastError_);
			break;
		}

		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchMenuSelect);
		break;
	}
	case(SearchPhase::SearchMenuSelect):
	{
		lastError_ = processSearchItem(context);
		if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS))
		{
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchStart);
			ui_.clearScreen();
			break;
		}

		searchItemController(bookUI, context, result);
		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchResultPrint);
		break;
	}
	case(SearchPhase::SearchResultPrint):
	{
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		break;
	}
	case(SearchPhase::SearchNextStart):
	{
		context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS))
		{
			context.err = wrapVariant<ResultVariant>(lastError_);
			ui_.clearScreen();
			break;
		}
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchSubMenuSelect);
		break;
	}
	case(SearchPhase::SearchSubMenuSelect):
	{
		if (context.menu == 0)
		{
			context.phase = wrapVariant<SearchPhase>(SearchPhase::Exit);
			vector<pair<PersonalData, int>>().swap(result);
			break;
		}

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
			ui_.clearScreen();
		}
		searchSubMenuController(bookUI, context, result);
		break;
	}
	case(SearchPhase::EditStart):
	{
		context.menu = inputH_.getInt(IntRule::PositiveOnly);

		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
		{
			context.err = wrapVariant<ResultVariant>(lastError_);
			break;
		}

		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchMenuSelect);
		break;
	}
	case(SearchPhase::EditItem):
	{
		if (context.menu == 0)
		{
			context.phase = wrapVariant<SearchPhase>(SearchPhase::Exit);
			break;
		}
		break;
	}
	case(SearchPhase::DeleteStart):
	{
		break;
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

void SearchMenu::searchSubMenuController(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result)
{
	switch (context.menu)
	{
	case (1):
	{
		processEditItem(bookUI, context, result);
		break;
	}
	case(2):
	{
		processDeleteItem(bookUI, context, result);
		break;
	}
	case(9):
	{
		frame_ = uiMsgH_.searchAgain(context.err);
		frame_(errorMsgH_);

		bool yesNo = inputH_.askYesNo();
		lastError_ = inputH_.getLastError();

		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS))
		{
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchNextStart);
			break;
		}

		if (yesNo)
		{
			context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchStart);
		}
		else
		{
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		}
		context.err = nullopt;
		break;
	}
	case(0):
	{
		context.phase = wrapVariant<SearchPhase>(SearchPhase::Exit);
		vector<pair<PersonalData, int>>().swap(result);
		break;
	}
	default:
		lastError_ = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		break;
	}
}

void SearchMenu::processEditItem(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& searchResult) 
{
	frame_ = uiMsgH_.searchEdit(context.err);
	frame_(errorMsgH_);

	int input = inputH_.getInt(IntRule::PositiveOnly);
	lastError_ = inputH_.getLastError();

	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		return;
	}

	int resultCount = static_cast<int>(searchResult.size());
	if (input > resultCount) 
	{
		lastError_ = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		return;
	}

	int i = input - 1;
	PersonalData dataToEdit = searchResult[i].first;
	int index = searchResult[i].second;

	EditMenu editMenu;
	optional<PersonalData> editResult = editMenu.run(bookUI, dataToEdit);

	//edit결과 처리
	if (editResult.has_value()) 
	{
		PersonalData editedData = editResult.value();
		AddOperationResult addResult = bookUI.extractAddressBook().edit(index, editedData);

		if (addResult == AddOperationResult::SUCCESS) 
		{
			frame_ = uiMsgH_.editSuccess(index, editedData.name);
			frame_(errorMsgH_);

			inputH_.getAnyKey();
			context.err = nullopt;

			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchStart);
		}
		else 
		{
			lastError_ = addResult;
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		}
	}
	else 
	{
		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
	}
}

void SearchMenu::processDeleteItem(AddressBookUI& bookUI, ContextData& context, std::vector<std::pair<PersonalData, int>>& searchResult) 
{
	frame_ = uiMsgH_.searchDelete(context.err);
	frame_(errorMsgH_);

	int input = inputH_.getInt(IntRule::PositiveOnly);
	lastError_ = inputH_.getLastError();

	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		return;
	}

	int resultCount = static_cast<int>(searchResult.size());
	if (input > resultCount) 
	{
		lastError_ = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		return;
	}

	int i = input - 1;
	string name = searchResult[i].first.name;
	int originalIndex = searchResult[i].second;

	context.err = nullopt;
	frame_ = uiMsgH_.deleteConfirm(context.err, i, name);
	frame_(errorMsgH_);

	bool yesNo = inputH_.askYesNo();
	lastError_ = inputH_.getLastError();

	if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(lastError_);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		return;
	}

	if (yesNo)
	{
		string removedName;
		RemoveOperationResult deleteResult = bookUI.extractAddressBook().remove(originalIndex, removedName);

		if (deleteResult == RemoveOperationResult::SUCCESS)
		{
			frame_ = uiMsgH_.deleteSuccess(input, removedName);
			frame_(errorMsgH_);

			//TODO: 마무리 절차 결정 후에 수정 필요
			cout << "Enter 키를 누르세요." << endl;

			inputH_.getAnyKey();
			context.err = nullopt;
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchStart);
		}
		else
		{
			lastError_ = deleteResult;
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		}
	}
	else
	{
		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
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

void SearchMenu::searchItemController(AddressBookUI& bookUI, ContextData& context, vector<pair<PersonalData, int>>& result)
{
	result.clear(); //기존 검색결과 초기화

	string input;

	//입력 받기
	if (context.menu == 1) 
	{
		input = inputH_.getString(StringRule::EmptyDisallow);
	}
	else if (context.menu >= 2 && context.menu <= 5) 
	{
		input = inputH_.getString(StringRule::EmptyAllow);
	}
	else 
	{
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
		lastError_ = context.err.value();
		return;
	}

	//입력에러
	ResultVariant inputError;
	inputError = inputH_.getLastError();
	if (!isVariantEqualTo<InputResult>(inputError, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(inputError);
		lastError_ = context.err.value();
		return;
	}

	context.err = nullopt;
	switch (context.menu)
	{
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
	default:
		break;
	}
}
