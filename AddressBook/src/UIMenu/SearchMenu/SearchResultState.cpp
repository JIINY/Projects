#include "SearchResultState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;

void SearchResultState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();
	int resultSize = static_cast<int>(owner_.accessSearchResult().size());

	owner_.drawLongTitle();
	owner_.drawResultTable();
	owner_.drawResultMsg();

	if (resultSize == 0) 
	{
		frame = uiMsgH.searchEmptySubMenu();
	}
	else 
	{
		frame = uiMsgH.searchSubMenu();
	}
	frame(errorMsgH);

	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

SearchPhase SearchResultState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int resultSize = static_cast<int>(owner_.accessSearchResult().size());

	context.menu = inputH.getInt(IntRule::ZeroOrPositive);
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}

	return processSubMenu(context.menu, resultSize);
}

SearchPhase SearchResultState::processSubMenu(int menu, int resultSize)
{
	if (resultSize == 0)
	{
		return processEmptyMenu(menu);
	}
	else
	{
		return processResultMenu(menu);
	}
}

SearchPhase SearchResultState::processEmptyMenu(int menu) 
{
	auto& context = owner_.getContext();
	ResultVariant error;

	switch (menu) {
	case 9: 
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Search);
		return SearchPhase::SearchStart;		
	}
	case 0: 
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Search);
		return SearchPhase::Exit;
	}
	default: 
	{
		error = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}
	}
}

SearchPhase SearchResultState::processResultMenu(int menu) 
{
	auto& context = owner_.getContext();
	context.err = nullopt;

	switch (context.menu)
	{
	case(1): 
	{
		owner_.setMode(SearchMode::Edit);
		return SearchPhase::EditStart;
	}
	case(2):
	{
		owner_.setMode(SearchMode::Delete);
		return SearchPhase::DeleteStart;
	}
	case(9): 
	{
		owner_.setMode(SearchMode::Search);
		return SearchPhase::SearchAgain;
	}
	case(0):
	{
		owner_.setMode(SearchMode::Search);
		return SearchPhase::Exit;
	}
	default: 
	{
		ResultVariant error = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}
	}
}
