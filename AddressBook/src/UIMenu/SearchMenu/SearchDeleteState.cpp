#include "SearchDeleteState.hpp"
#include <vector>
#include <optional>
#include <utility>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchDeleteState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchDelete(context.err);
	frame(errorMsgH);
}

SearchPhase SearchDeleteState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	int resultCount = static_cast<int>(owner_.accessSearchResult().size());

	int input = -1;
	ResultVariant result = inputH.getInt(IntRule::PositiveOnly, input);
	if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(result);
		return SearchPhase::SearchResult;
	}
	else if (input > resultCount) 
	{
		result = InputResult::WRONG_NUMBER;
		context.err = wrapVariant<ResultVariant>(result);
		return SearchPhase::SearchResult;
	}

	//성공
	context.menu = input - 1;
	context.err = nullopt;
	return SearchPhase::DeleteItem;
}
