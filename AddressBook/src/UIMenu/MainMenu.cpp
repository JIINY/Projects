#include "MainMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "AddMenu.hpp"
#include "ViewMenu.hpp"
#include "SearchMenu.hpp"
using namespace std;


void MainMenu::run() {
	processMainMenu();
}
ResultVariant MainMenu::getLastError() const { return this->lastError; }


void MainMenu::processMainMenu() {
	int menu = 0;
	optional<ResultVariant> err = nullopt;

	while (true) {

		//메인메뉴 + 에러메세지 출력
		frame = uiMsgH.mainMenu();
		frame(errorMsgH);

		//메뉴선택 출력
		frame = uiMsgH.menuSelect(err);
		frame(errorMsgH);


		//메뉴 입력처리
		menu = inputH.getInt(IntRule::ZeroOrPositive);
		lastError = inputH.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError, InputResult::SUCCESS)) {
			err = wrapVariant<ResultVariant>(lastError);
			ui.clearScreen();
			continue;
		}

		//메뉴 선택처리
		if (menu == 0) { break; }

		lastError = mainMenuController(menu);
		if (!isVariantEqualTo<MenuSelectResult>(lastError, MenuSelectResult::SUCCESS)) {
			err = wrapVariant<ResultVariant>(lastError);
			UIUtils::clearScreen();
			continue;
		}

		//에러가 없다면 초기화
		err = nullopt;
		ui.clearScreen();
	}
}

ResultVariant MainMenu::mainMenuController(int input) {
	UIUtils::clearScreen();

	switch (input) {
	case 1: {
		AddMenu add;
		add.run();
		return MenuSelectResult::SUCCESS;
	}
	case 2: {
		if (book->getLength() == 0) {
			return MenuSelectResult::EMPTY_ADDRESSBOOK;
		}
		ViewMenu view;
		view.run();
		return MenuSelectResult::SUCCESS;
	}
	case 3: {
		if (book->getLength() == 0) {
			return MenuSelectResult::EMPTY_ADDRESSBOOK;
		}
		SearchMenu search;
		search.run();
		return MenuSelectResult::SUCCESS;
	}
	default:
		return MenuSelectResult::WRONG_INDEX;
	}
}
