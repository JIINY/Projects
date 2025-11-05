#include "ViewMenu.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <cctype>
#include <algorithm>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "../../UI/AddressBookUI.hpp"
using namespace std;


void ViewMenu::run(AddressBookUI& bookUI)
{
	ContextData context;
	context.err = nullopt;
	int length = bookUI.getLength();
	int pageIndex = 0;
	ViewPhase currentPhase = ViewPhase::Stay;

	while (currentPhase != ViewPhase::Exit)
	{
		ui_.clearScreen();
		
		//타이틀
		frame_ = uiMsgH_.viewTitle(context.err);
		frame_(errorMsgH_);

		//페이지
		draw(bookUI, context, pageIndex, length);

		//입력 처리
		ViewPhase nextPhase = update(context, pageIndex, length);
		
		if (nextPhase == ViewPhase::Next) 
		{
			pageIndex += 1;
		}
		else if (nextPhase == ViewPhase::Prev) 
		{
			pageIndex -= 1;
		}
		currentPhase = nextPhase;
	}
}

void ViewMenu::draw(AddressBookUI& bookUI, ContextData& context, int page, int length) 
{
	int startIndex = page * 10;
	int endIndex = min(startIndex + 10, length);

	if (length == 0) 
	{
		frame_ = uiMsgH_.searchEmpty();
		frame_(errorMsgH_);
	}

	for (int i = startIndex; i < endIndex; ++i)
	{
		context.p = bookUI.getPersonalDataAt(i);
		context.sub = ui_.getPersonalDataTableFormat(context.p);

		int displayNum = i + 1;
		if (i == (endIndex - 1)) 
		{
			frame_ = uiMsgH_.tableDataBottom(context.err, displayNum, context.sub);
		}
		else 
		{
			int remainder = (displayNum) % 10;
			if (remainder == 5)
			{
				frame_ = uiMsgH_.tableDataCenter(context.err, displayNum, context.sub);
			}
			else 
			{
				frame_ = uiMsgH_.tableDataNormal(context.err, displayNum, context.sub);
			}
		}
		frame_(errorMsgH_);
	}

	if (endIndex == length) 
	{
		frame_ = uiMsgH_.tableComplete();
		frame_(errorMsgH_);
		frame_ = uiMsgH_.tableCommand(context.err);
	}
	else 
	{
		frame_ = uiMsgH_.tableContinue();
		frame_(errorMsgH_);
		frame_ = uiMsgH_.tableCommand(context.err);
	}
	frame_(errorMsgH_);
}

ViewPhase ViewMenu::update(ContextData& context, int page, int length)
{
	PagingPhase phase = inputH_.getPagingInput(PagingMenu::View);
	context.err = inputH_.getLastError();

	switch (phase) {
	case PagingPhase::Next:
	{
		bool isLastPage = ((page + 1) * 10) >= length;
		if (isLastPage)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_END);
			return ViewPhase::Stay;
		}
		context.err = nullopt;
		return ViewPhase::Next;
	}
	case PagingPhase::Prev:
	{
		if (page == 0)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_START);
			return ViewPhase::Stay;
		}
		context.err = nullopt;
		return ViewPhase::Prev;
	}
	case PagingPhase::Exit:
		context.err = nullopt;
		return ViewPhase::Exit;
	default:
	{
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_COMMAND);
		return ViewPhase::Stay;
	}
	}
}
