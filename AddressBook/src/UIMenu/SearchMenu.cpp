#pragma once
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
		frame = uiMsgH.searchEmpty();
		frame(errorMsgH);
	}
	else {
		for (int i = page; i < length && i < page + 10; i++) {
			context.p = result[i].first;
			context.sub = ui.getPersonalDataTableFormat(context.p);

			int remainder = (i + 1) % 10;
			if (remainder == 5) {
				frame = uiMsgH.tableDataCenter(context.err, i + 1, context.sub);
			}
			else if (remainder == 0 || (i + 1) == length) {
				frame = uiMsgH.tableDataBottom(context.err, i + 1, context.sub);
				frame(errorMsgH);

				if (i + 1 == length) {
					frame = uiMsgH.tableSearchEnd(context.err);
				}
				else {
					frame = uiMsgH.tableContinue(context.err);
				}
			}
			else {
				frame = uiMsgH.tableDataNormal(context.err, i + 1, context.sub);
			}
			frame(errorMsgH);
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
			frame = uiMsgH.searchMenu();
			frame(errorMsgH);
			frame = uiMsgH.menuSelect(context.err);
			frame(errorMsgH);
			searchMenuController(context, result);
			break;
		}
		case(SearchPhase::SearchMenuSelect): {
			if (context.menu == 0) { 
				context.phase = wrapVariant<PhaseVariant>(SearchPhase::Exit);
				break; 
			}

			frame = uiMsgH.searchMenu();
			frame(errorMsgH);
			frame = uiMsgH.menuSelect(context.err);
			frame(errorMsgH);
			searchMenuController(context, result);
			break;
		}
		case(SearchPhase::SearchResultPrint): {
			frame = uiMsgH.searchResult();
			frame(errorMsgH);

			printSearchResultTable(context, result);
			searchMenuController(context, result);
			break;
		}
		case(SearchPhase::SearchNextStart): {
			frame = uiMsgH.searchResult();
			frame(errorMsgH);
			printSearchResultTable(context, result);

			int length = static_cast<int>(result.size());
			if (length == 0) {
				frame = uiMsgH.searchEmptySubMenu();
				frame(errorMsgH);
			}
			else {
				frame = uiMsgH.searchSubMenu();
				frame(errorMsgH);
			}
			frame = uiMsgH.menuSelect(context.err);
			frame(errorMsgH);

			searchMenuController(context, result);
			continue;
		}
		case(SearchPhase::SearchSubMenuSelect): {
			searchMenuController(context, result);
			
			if (context.menu == 9) { break; }
			break;
		}
		case(SearchPhase::EditStart): {
			frame = uiMsgH.searchResult();
			frame(errorMsgH);
			printSearchResultTable(context, result);

			frame = uiMsgH.searchEdit(context.err);
			frame(errorMsgH);

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

		ui.clearScreen();
		if (phase == SearchPhase::Exit) {
			break;
		}
	}
}

void SearchMenu::searchMenuController(ContextData& context, vector<pair<PersonalData, int>>& result) {
	SearchPhase phase = unwrapVariant<SearchPhase>(context.phase);
	switch (phase) {
	case(SearchPhase::SearchStart): {
		context.menu = inputH.getInt(IntRule::ZeroOrPositive);

		lastError = inputH.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			break;
		}

		context.err = nullopt;
		context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchMenuSelect);
		break;
	}
	case(SearchPhase::SearchMenuSelect): {
		lastError = processSearchItem(context);
		if (!isVariantEqualTo<MenuSelectResult>(lastError, MenuSelectResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			context.phase = wrapVariant<SearchPhase>(SearchPhase::SearchStart);
			ui.clearScreen();
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
		context.menu = inputH.getInt(IntRule::ZeroOrPositive);
		lastError = inputH.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			ui.clearScreen();
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
			lastError = processSearchEmptySubMenu(context);
		}
		else {
			lastError = processSearchSubMenu(context);
		}

		if (!isVariantEqualTo<MenuSelectResult>(lastError, MenuSelectResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
			ui.clearScreen();
		}
		searchSubMenuController(context);
		break;
	}
	case(SearchPhase::EditStart): {
		context.menu = inputH.getInt(IntRule::PositiveOnly);

		lastError = inputH.getLastError();
		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
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
		frame = uiMsgH.searchAgain(context.err);
		frame(errorMsgH);
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
		frame = uiMsgH.searchEdit(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case(2): {
		frame = uiMsgH.searchDelete(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case(9): {
		frame = uiMsgH.searchAgain(context.err);
		frame(errorMsgH);
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
		bool yesNo = inputH.askYesNo();
		lastError = inputH.getLastError();

		if (!isVariantEqualTo <InputResult>(lastError, InputResult::SUCCESS)) {
			context.err = wrapVariant<ResultVariant>(lastError);
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
	frame = uiMsgH.searchTitle();
	frame(errorMsgH);

	switch (context.menu) {
	case 1: {
		frame = uiMsgH.editName(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case 2: {
		frame = uiMsgH.editPhone(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case 3: {
		frame = uiMsgH.editAddress(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case 4: {
		frame = uiMsgH.editZipCode(context.err);
		frame(errorMsgH);
		return MenuSelectResult::SUCCESS;
	}
	case 5: {
		frame = uiMsgH.editEmail(context.err);
		frame(errorMsgH);
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
