#include "SearchMenu.hpp"
#include <vector>
#include <optional>
#include <algorithm>
#include <utility>
#include "../Common/DataType.hpp"
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"


void SearchMenu::run() {
	processSearchMenu();
}

void SearchMenu::printSearchResultTable(ContextData& context, vector<pair<PersonalData, int>> result) {
	int page = 0;

	int length = static_cast<int>(result.size());
	if (length == 0) {
		frame_ = uiMsgH_.searchEmpty();
		frame_(errorMsgH_);
	}
	else {
		for (int i = page; i < length && i < page + 10; i++) {
			context.p = result[i].first;
			context.sub = ui_.getPersonalDataTableFormat(context.p);

			int remainder = (i + 1) % 10;
			if (remainder == 5) {
				frame_ = uiMsgH_.tableDataCenter(context.err, i + 1, context.sub);
			}
			else if (remainder == 0 || (i + 1) == length) {
				frame_ = uiMsgH_.tableDataBottom(context.err, i + 1, context.sub);
				frame_(errorMsgH_);

				if (i + 1 == length) {
					frame_ = uiMsgH_.tableSearchEnd(context.err);
				}
				else {
					frame_ = uiMsgH_.tableContinue(context.err);
				}
			}
			else {
				frame_ = uiMsgH_.tableDataNormal(context.err, i + 1, context.sub);
			}
			frame_(errorMsgH_);
		}
	}
}

void SearchMenu::processSearchMenu() {
	ContextData context;
	context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchStart);
	vector<pair<PersonalData, int>> result;

	while (true) {
		SearchPhase phase = unwrapVariant<SearchPhase>(context.phase);
		switch (phase) {
		case (SearchPhase::SearchStart): {
			searchMenuController(context, result);
			frame_ = uiMsgH_.searchMenu();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			break;
		}
		case(SearchPhase::SearchMenuSelect): {
			if (context.menu == 0) { 
				context.phase = wrapVariant<PhaseVariant>(SearchPhase::Exit);
				break; 
			}

			searchMenuController(context, result);
			frame_ = uiMsgH_.searchMenu();
			frame_(errorMsgH_);
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);
			break;
		}
		case(SearchPhase::SearchResultPrint): {
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);

			printSearchResultTable(context, result);
			searchMenuController(context, result);
			break;
		}
		case(SearchPhase::SearchNextStart): {
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);
			printSearchResultTable(context, result);

			int length = static_cast<int>(result.size());
			if (length == 0) {
				frame_ = uiMsgH_.searchEmptySubMenu();
				frame_(errorMsgH_);
			}
			else {
				frame_ = uiMsgH_.searchSubMenu();
				frame_(errorMsgH_);
			}
			frame_ = uiMsgH_.menuSelect(context.err);
			frame_(errorMsgH_);

			searchMenuController(context, result);
			continue;
		}
		case(SearchPhase::SearchSubMenuSelect): {
			searchMenuController(context, result);
			
			if (context.menu == 9) { break; }
			break;
		}
		case(SearchPhase::EditStart): {
			frame_ = uiMsgH_.searchResult();
			frame_(errorMsgH_);
			printSearchResultTable(context, result);

			frame_ = uiMsgH_.searchEdit(context.err);
			frame_(errorMsgH_);

			searchMenuController(context, result);
			break;
		}
		case(SearchPhase::EditItem): {
			searchMenuController(context, result);
			continue;
		}
		case(SearchPhase::DeleteStart): {
			//frame = uiMsgH.selectItem();
			//frame(errorMsgH);
			searchMenuController(context, result);
			break;
		}
		}

		ui_.clearScreen();
		if (phase == SearchPhase::Exit) {
			break;
		}
	}
}

void SearchMenu::searchMenuController(ContextData& context, vector<pair<PersonalData, int>>& result) {
	SearchPhase phase = unwrapVariant<SearchPhase>(context.phase);
	switch (phase) {
	case(SearchPhase::SearchStart): {
		context.menu = inputH_.getInt(IntRule::ZeroOrPositive);

		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			break;
		}

		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchMenuSelect);
		break;
	}
	case(SearchPhase::SearchMenuSelect): {
		lastError_ = processSearchItem(context);
		if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchStart);
			ui_.clearScreen();
			break;
		}

		searchItemController(context, result);
		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchResultPrint);
		break;
	}
	case(SearchPhase::SearchResultPrint): {
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		break;
	}
	case(SearchPhase::SearchNextStart): {
		context.menu = inputH_.getInt(IntRule::ZeroOrPositive);
		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			ui_.clearScreen();
			break;
		}
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchSubMenuSelect);
		break;
	}
	case(SearchPhase::SearchSubMenuSelect): {
		if (context.menu == 0) {
			context.phase = wrapVariant<SearchPhase>(SearchPhase::Exit);
			vector<pair<PersonalData, int>>().swap(result);
			break;
		}

		int length = static_cast<int>(result.size());
		if (length == 0) {
			lastError_ = processSearchEmptySubMenu(context);
		}
		else {
			lastError_ = processSearchSubMenu(context);
		}

		if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			ui_.clearScreen();
		}
		searchSubMenuController(context);
		break;
	}
	case(SearchPhase::EditStart): {
		context.menu = inputH_.getInt(IntRule::PositiveOnly);

		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			break;
		}

		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchMenuSelect);
		break;
	}
	case(SearchPhase::EditItem): {
		if (context.menu == 0) {
			context.phase = wrapVariant<SearchPhase>(SearchPhase::Exit);
			break;
		}
		break;
	}
	case(SearchPhase::DeleteStart): {
		break;
	}
	}
}

ResultVariant SearchMenu::processSearchEmptySubMenu(ContextData& context) {
	switch (context.menu) {
	case(9): {
		frame_ = uiMsgH_.searchAgain(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default: {
		return MenuSelectResult::WRONG_INDEX;
	}
	}
}

ResultVariant SearchMenu::processSearchSubMenu(ContextData& context) {
	switch (context.menu) {
	case(1): {
		frame_ = uiMsgH_.searchEdit(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case(2): {
		frame_ = uiMsgH_.searchDelete(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case(9): {
		frame_ = uiMsgH_.searchAgain(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default: {
		return MenuSelectResult::WRONG_INDEX;
	}
	}
}

void SearchMenu::searchSubMenuController(ContextData& context) {
	switch (context.menu) {
	case (1): {
		context.phase = wrapVariant<SearchPhase>(SearchPhase::EditStart);
		break;
	}
	case(2): {
		context.phase = wrapVariant<SearchPhase>(SearchPhase::DeleteStart);
		break;
	}
	case(9): {

		bool yesNo = inputH_.askYesNo();
		lastError_ = inputH_.getLastError();

		if (!isVariantEqualTo <InputResult>(lastError_, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError_);
			context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchNextStart);
			break;
		}

		if (yesNo) {
			context.phase = wrapVariant<PhaseVariant>(SearchPhase::SearchStart);
		}
		else {
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		}
		context.err = nullopt;
		break;
	}
	default:
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchNextStart);
		break;
	}
}

ResultVariant SearchMenu::processSearchItem(ContextData& context) {
	UIUtils::clearScreen();
	frame_ = uiMsgH_.searchTitle();
	frame_(errorMsgH_);

	switch (context.menu) {
	case 1: {
		frame_ = uiMsgH_.editName(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 2: {
		frame_ = uiMsgH_.editPhone(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 3: {
		frame_ = uiMsgH_.editAddress(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 4: {
		frame_ = uiMsgH_.editZipCode(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	case 5: {
		frame_ = uiMsgH_.editEmail(context.err);
		frame_(errorMsgH_);
		return MenuSelectResult::SUCCESS;
	}
	default:
		return MenuSelectResult::WRONG_INDEX;
	}
}

void SearchMenu::searchItemController(ContextData& context, vector<pair<PersonalData, int>>& result) {
	result.clear(); //기존 검색결과 초기화

	int length = book->getLength();
	string input;
	switch (context.menu) {
	case 1: {	
		input = inputH.getString(StringRule::EmptyDisallow);
		for (int i = 0; i < length; i++) {
			const string& s = book->getNameAt(i);
			if (input.empty() && s.empty() || !input.empty() && s.find(input) != string::npos) {
				PersonalData p = book->getPersonalDataAt(i);
				result.push_back(make_pair(p, i));
			}
		}
		break;
	}
	case 2: {		
		input = inputH.getString(StringRule::EmptyAllow);
		for (int i = 0; i < length; i++) {
			const string& s = book->getPhoneAt(i);
			if (input.empty() && s.empty() || !input.empty() && s.find(input) != string::npos) {
				PersonalData p = book->getPersonalDataAt(i);
				result.push_back(make_pair(p, i));
			}
		}
		break;
	}
	case 3: {
		input = inputH.getString(StringRule::EmptyAllow);
		for (int i = 0; i < length; i++) {
			const string& s = book->getAddressAt(i);
			if (input.empty() && s.empty() || !input.empty() && s.find(input) != string::npos) {
				PersonalData p = book->getPersonalDataAt(i);
				result.push_back(make_pair(p, i));
			}
		}
		break;
	}
	case 4: {
		input = inputH.getString(StringRule::EmptyAllow);
		for (int i = 0; i < length; i++) {
			const string& s = book->getZipCodeAt(i);
			if (input.empty() && s.empty() || !input.empty() && s.find(input) != string::npos) {
				PersonalData p = book->getPersonalDataAt(i);
				result.push_back(make_pair(p, i));
			}
		}
		break;
	}
	case 5: {
		input = inputH.getString(StringRule::EmptyAllow);
		for (int i = 0; i < length; i++) {
			const string& s = book->getEmailAt(i);
			if (input.empty() && s.empty() || !input.empty() && s.find(input) != string::npos) {
				PersonalData p = book->getPersonalDataAt(i);
				result.push_back(make_pair(p, i));
			}
		}
		break;
	}
	default:
		break;
	}
}
