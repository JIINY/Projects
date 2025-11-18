#include "SearchEditState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include <algorithm>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchEditState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchEdit(context.err);
	frame(errorMsgH);
}

SearchPhase SearchEditState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int resultCount = static_cast<int>(owner_.accessSearchResult().size());

	int currentPage = owner_.getCurrentPage();
	int minNumOnPage = (currentPage * 10) + 1;
	int maxNumOnPage = min((currentPage + 1) * 10, resultCount);

	int input = -1;
	CommandPhase phase = inputH.getSearchPagingInput(input);
	switch (phase) {
	case CommandPhase::PositiveNums: 
	{
		if (input < minNumOnPage || input > maxNumOnPage) 
		{
			context.err = wrapVariant<ResultVariant>(InputResult::WRONG_NUMBER);
			return SearchPhase::EditStart;
		}

		context.menu = input - 1;
		context.err = nullopt;
		return SearchPhase::EditItem;
	}
	case CommandPhase::Next:
	{
		if (maxNumOnPage < resultCount)
		{
			owner_.setCurrentPage(currentPage + 1);
			context.err = nullopt;
		}
		else
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_END);
		}
		return SearchPhase::EditStart;
	}
	case CommandPhase::Prev:
	{
		if (currentPage > 0) 
		{
			owner_.setCurrentPage(currentPage - 1);
			context.err = nullopt;
		}
		else 
		{
			context.err = wrapVariant<ResultVariant>(MenuSelectResult::PAGE_START);
		}
		return SearchPhase::EditStart;
	}
	case CommandPhase::Exit:
	{
		context.err = nullopt;
		return SearchPhase::SearchResult;
	}
	case CommandPhase::Enter: 
	{
		context.err = nullopt;
		return SearchPhase::SearchResult;
	}
	case CommandPhase::Error:
	default:
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_COMMAND);
		return SearchPhase::SearchResult;
	}
}

