#include "MainMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
#include "AddMenu.hpp"
#include "ViewMenu.hpp"
#include "SearchMenu.hpp"
using namespace std;


void MainMenu::run(AddressBookUI& bookUI)
{
	processMainMenu(bookUI);
}
ResultVariant MainMenu::getLastError() const { return this->lastError_; }


void MainMenu::processMainMenu(AddressBookUI& bookUI)
{
	int menu = 0;
	optional<ResultVariant> err = nullopt;

	while (true)
	{
		//���θ޴� + �����޼��� ���
		frame_ = uiMsgH_.mainMenu();
		frame_(errorMsgH_);

		//�޴����� ���
		frame_ = uiMsgH_.menuSelect(err);
		frame_(errorMsgH_);


		//�޴� �Է�ó��
		menu = inputH_.getInt(IntRule::ZeroOrPositive);
		lastError_ = inputH_.getLastError();
		if (!isVariantEqualTo<InputResult>(lastError_, InputResult::SUCCESS))
		{
			err = wrapVariant<ResultVariant>(lastError_);
			ui_.clearScreen();
			continue;
		}

		//�޴� ����ó��
		if (menu == 0) { break; }

		lastError_ = mainMenuController(bookUI, menu);
		if (!isVariantEqualTo<MenuSelectResult>(lastError_, MenuSelectResult::SUCCESS))
		{
			err = wrapVariant<ResultVariant>(lastError_);
			UIUtils::clearScreen();
			continue;
		}

		//������ ���ٸ� �ʱ�ȭ
		err = nullopt;
		ui_.clearScreen();
	}
}

ResultVariant MainMenu::mainMenuController(AddressBookUI& bookUI, int input)
{
	UIUtils::clearScreen();

	switch (input)
	{
	case 1:
	{
		AddMenu add;
		add.run(bookUI);
		return MenuSelectResult::SUCCESS;
	}
	case 2:
	{
		if (bookUI.getLength() == 0) { return MenuSelectResult::EMPTY_ADDRESSBOOK; }
		ViewMenu view;
		view.run(bookUI);
		return MenuSelectResult::SUCCESS;
	}
	case 3:
	{
		if (bookUI.getLength() == 0) { return MenuSelectResult::EMPTY_ADDRESSBOOK; }
		SearchMenu search;
		search.run(bookUI);
		return MenuSelectResult::SUCCESS;
	}
	default:
		return MenuSelectResult::WRONG_INDEX;
	}
}
