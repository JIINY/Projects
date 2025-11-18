#include "SearchDeleteMenuState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include <algorithm>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchDeleteMenuState::draw()
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchDeleteSubMenu(context.err);
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

SearchPhase SearchDeleteMenuState::update()
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
		owner_.setMode(SearchMode::Edit);
		return SearchPhase::EditStart;
	}
	case CommandPhase::Search:
	{
		owner_.setMode(SearchMode::Search);
		return SearchPhase::SearchStart;
	}
	case CommandPhase::Exit:
	{
		owner_.setMode(SearchMode::Search);
		return SearchPhase::Exit;
	}
	case CommandPhase::Next:
	{
		int page = owner_.getCurrentPage();
		int length = static_cast<int>(owner_.accessSearchResult().size());

		bool isLastPage = ((page + 1) * 10) >= length;
		if (isLastPage)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_END);
			return SearchPhase::SearchResult;
		}
		owner_.setCurrentPage(page + 1);
		context.err = nullopt;
		return SearchPhase::SearchResult;
	}
	case CommandPhase::Prev:
	{
		int page = owner_.getCurrentPage();
		if (page == 0)
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_START);
			return SearchPhase::SearchResult;
		}
		owner_.setCurrentPage(page - 1);
		context.err = nullopt;
		return SearchPhase::SearchResult;
	}
	case CommandPhase::PositiveNums:
	{
		int length = static_cast<int>(owner_.accessSearchResult().size());
		int currentPage = owner_.getCurrentPage();
		int minNumOnPage = (currentPage * 10) + 1;
		int maxNumOnPage = min((currentPage + 1) * 10, length);

		if (input < minNumOnPage || input > maxNumOnPage)
		{
			context.err = wrapVariant<ResultVariant>(InputResult::WRONG_NUMBER);
			return SearchPhase::SearchResult;
		}

		context.menu = input - 1;
		context.err = nullopt;
		return SearchPhase::DeleteItem;
	}
	default:
	{
		ResultVariant error = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchResult;
	}
	}
}
