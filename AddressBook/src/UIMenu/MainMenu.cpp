#include "MainMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
#include "AddMenu/AddMenu.hpp"
#include "ViewMenu/ViewMenu.hpp"
#include "SearchMenu/SearchMenu.hpp"
#include "DeleteMenu/DeleteAllMenu.hpp"
using namespace std;


void MainMenu::run(AddressBookUI& bookUI)
{
	processMainMenu(bookUI);
}

void MainMenu::processMainMenu(AddressBookUI& bookUI)
{
	int menu = 0;
	optional<ResultVariant> err = nullopt;

	while (true)
	{
		//메인메뉴 + 에러메세지 출력
		frame_ = uiMsgH_.mainMenu();
		frame_(errorMsgH_);

		//메뉴선택 출력
		frame_ = uiMsgH_.menuSelect(err);
		frame_(errorMsgH_);


		//메뉴 입력처리
		int menu = -1;
		ResultVariant result = inputH_.getInt(IntRule::ZeroOrPositive, menu);
		if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS))
		{
			err = wrapVariant<ResultVariant>(result);
			ui_.clearScreen();
			continue;
		}

		//메뉴 선택처리
		if (menu <= 0) { break; }

		result = mainMenuController(bookUI, menu);
		if (!isVariantEqualTo<MenuSelectResult>(result, MenuSelectResult::SUCCESS))
		{
			err = wrapVariant<ResultVariant>(result);
			UIUtils::clearScreen();
			continue;
		}

		//에러가 없다면 초기화
		err = nullopt;
		ui_.clearScreen();
	}
}

ResultVariant MainMenu::mainMenuController(AddressBookUI& bookUI, int input)
{
	if (input != 9) 
	{
		UIUtils::clearScreen();
	}

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
	case 9: 
	{
		DeleteAllMenu deleteAllMenu;
		deleteAllMenu.run(bookUI, DBConfig::SAVEFILE);
		return MenuSelectResult::SUCCESS;
	}
	default:
		return MenuSelectResult::WRONG_INDEX;
	}
}
