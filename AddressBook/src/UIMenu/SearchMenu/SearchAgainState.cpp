#include "SearchAgainState.hpp"
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;


void SearchAgainState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchAgain(context.err);
	frame(errorMsgH);
}

SearchPhase SearchAgainState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	ResultVariant result = inputH.askYesNo();
	context.err = nullopt;
	if (isVariantEqualTo<InputResult>(result, InputResult::YES))
	{
		return SearchPhase::SearchStart;
	}
	else if (isVariantEqualTo<InputResult>(result, InputResult::NO))
	{
		return SearchPhase::SearchList;
	}

	context.err = wrapVariant<ResultVariant>(result);
	return SearchPhase::SearchAgain;
}
