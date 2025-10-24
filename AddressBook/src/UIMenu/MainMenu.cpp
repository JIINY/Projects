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

		//���θ޴� + �����޼��� ���
		frame = uiMsgH.mainMenu();
		frame(errorMsgH);

		//�޴����� ���
		frame = uiMsgH.menuSelect(err);
		frame(errorMsgH);


		//�޴� �Է�ó��
		menu = inputH.getInt(IntRule::ZeroOrPositive);
		lastError = inputH.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError, InputResult::SUCCESS)) {
			err = wrapVariant<ResultVariant>(lastError);
			ui.clearScreen();
			continue;
		}

		//�޴� ����ó��
		if (menu == 0) { break; }

		lastError = mainMenuController(menu);
		if (!isVariantEqualTo<MenuSelectResult>(lastError, MenuSelectResult::SUCCESS)) {
			err = wrapVariant<ResultVariant>(lastError);
			UIUtils::clearScreen();
			continue;
		}

		//������ ���ٸ� �ʱ�ȭ
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
