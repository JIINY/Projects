#include "SearchEmptyMenuState.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchEmptyMenuState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchEmptySubMenu(context.err);
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

SearchPhase SearchEmptyMenuState::update()
{
	owner_.setMode(SearchMode::SearchEmpty);
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	int input = -1;
	CommandPhase result = inputH.getSearchPagingInput(input);
	if (result == CommandPhase::Error)
	{
		ResultVariant error = InputResult::FAIL;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchList;
	}

	switch (result) {
	case CommandPhase::Search:
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Search);
		return SearchPhase::SearchStart;
	}
	case CommandPhase::Exit: 
	{
		context.err = nullopt;
		owner_.setMode(SearchMode::Search);
		return SearchPhase::Exit;
	}
	default:
	{
		ResultVariant error = MenuSelectResult::WRONG_COMMAND;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchList;
	}
	}

}
