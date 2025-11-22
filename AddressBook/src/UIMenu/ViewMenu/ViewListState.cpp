#include "ViewListState.hpp"
#include <algorithm>
#include <variant>
#include <optional>
#include "../../UI/AddressBookUI.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ViewMenu.hpp"
using namespace std;


void ViewListState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	auto* bookUI = owner_.getBookUI();
	int length = owner_.getLength();
	int& page = owner_.getPage();

	if (length > 0 && (page * 10) >= length) 
	{
		page = (length - 1) / 10; //삭제 후 돌아왔을 때 페이지가 범위를 벗어난 경우
	}
	else if (length == 0) 
	{
		page = 0;
	}

	frame = uiMsgH.viewTitle(context.err);
	frame(errorMsgH);

	int startIndex = page * 10;
	int endIndex = min(startIndex + 10, length);

	for (int i = startIndex; i < endIndex; ++i)
	{
		context.p = bookUI->getPersonalDataAt(i);

		int displayNum = i + 1;
		if (i == (endIndex - 1))
		{
			frame = uiMsgH.tableDataBottom(context.err, displayNum, context.p);
		}
		else
		{
			int remainder = (displayNum) % 10;
			if (remainder == 5)
			{
				frame = uiMsgH.tableDataCenter(context.err, displayNum, context.p);
			}
			else
			{
				frame = uiMsgH.tableDataNormal(context.err, displayNum, context.p);
			}
		}
		frame(errorMsgH);
	}

	if (endIndex == length)
	{
		frame = uiMsgH.tableComplete();
		frame(errorMsgH);
		frame = uiMsgH.tableCommandInputMessage(context.err);
	}
	else
	{
		frame = uiMsgH.tableCommand();
		frame(errorMsgH);
		frame = uiMsgH.tableCommandInputMessage(context.err);
	}
	frame(errorMsgH);
}

ViewPhase ViewListState::update() 
{
	if (owner_.getLength() == 0) 
	{
		return ViewPhase::Empty;
	}

	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int length = owner_.getLength();
	int& page = owner_.getPage();
	
	int input = -1;
	CommandPhase result = inputH.getViewPagingInput(input);

	switch (result) {
	case CommandPhase::PositiveNums: 
	{
		int targetIndex = input - 1;
		if (targetIndex < 0 || targetIndex >= length) 
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
			return ViewPhase::List;
		}

		int pageStartIndex = page * 10;
		int pageEndIndex = pageStartIndex + 10;

		if (targetIndex < pageStartIndex || targetIndex >= pageEndIndex) 
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_INDEX);
			return ViewPhase::List;
		}
		context.menu = targetIndex;
		context.err = nullopt;
		return ViewPhase::Action;
	}
	case CommandPhase::Stay:
	{
		context.err = nullopt;
		return ViewPhase::List;
	}
	case CommandPhase::Enter:
	{
		context.err = nullopt;
		return ViewPhase::List;
	}
	case CommandPhase::Exit:
	{
		context.err = nullopt;
		return ViewPhase::Exit;
	}
	case CommandPhase::Next:
	{
		bool isLastPage = ((page + 1) * 10) >= length;
		if (isLastPage)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_END);
		}
		else 
		{
			context.err = nullopt;
			page++;
		}
		return ViewPhase::List;
	}
	case CommandPhase::Prev:
	{
		if (page == 0)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_START);
		}
		else 
		{
			context.err = nullopt;
			page--;
		}
		return ViewPhase::List;
	}
	default:
	{
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_COMMAND);
		return ViewPhase::List;
	}
	}
}
