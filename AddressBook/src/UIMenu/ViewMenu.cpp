#include "ViewMenu.hpp"
#include <iostream>
#include <optional>
#include "../UI/UICommonData.hpp"
#include "../UI/UICommonHeader.hpp"
#include "../UI/AddressBookUI.hpp"
using namespace std;


void ViewMenu::processView(AddressBookUI& bookUI)
{
	ContextData context;
	int length = bookUI.getLength();
	int page = 0;

	while (page < length)
	{
		ui_.clearScreen();
		context.err = nullopt;
		
		//타이틀
		frame_ = uiMsgH_.viewTitle(context.err);
		frame_(errorMsgH_);

		//페이지
		drawPage(bookUI, context, page, length);

		//입력 처리
		if (handlePageInput(context, page, length)) 
		{
			break;
		}

		page += 10;
	}
}

void ViewMenu::drawPage(AddressBookUI& bookUI, ContextData& context, int page, int length) 
{
	for (int i = page; i < length && i < page + 10; i++)
	{
		context.p = bookUI.getPersonalDataAt(i);
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
				frame_ = uiMsgH_.tableComplete(context.err);
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

bool ViewMenu::handlePageInput(ContextData& context, int page, int length) 
{
	bool isLastPage = (page + 10) >= length;

	if (isLastPage)
	{
		inputH_.getAnyKey();
		return true;
	}

	if (inputH_.anyKeyOrQuit())
	{
		frame_ = uiMsgH_.tableStop(context.err);
		frame_(errorMsgH_);

		if (inputH_.askYesNo())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}