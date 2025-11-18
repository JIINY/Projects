#include "SearchActionMenuState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include <algorithm>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchActionMenuState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchActionSubMenu(context.err);
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

SearchPhase SearchActionMenuState::update()
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	int input = -1;
	CommandPhase result = inputH.getSearchPagingInput(input);
	if (result == CommandPhase::Error)
	{
		ResultVariant error = InputResult::FAIL;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}

	switch (result)
	{
	case CommandPhase::Edit:
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Edit);
		return SearchPhase::EditItem;
	}
	case CommandPhase::Delete:
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Delete);
		return SearchPhase::DeleteItem;
	}
	case CommandPhase::Cancel:
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Search);
		return SearchPhase::SearchResult;
	}
	default:
	{
		owner_.setMode(SearchMode::Action);
		ResultVariant error = MenuSelectResult::WRONG_COMMAND;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}
	}
}
