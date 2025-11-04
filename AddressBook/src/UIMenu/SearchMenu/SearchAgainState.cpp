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

	bool yesNo = inputH.askYesNo();
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchAgain;
	}

	context.err = nullopt;
	if (yesNo) 
	{
		return SearchPhase::SearchStart;
	}
	else 
	{
		return SearchPhase::SearchResult;
	}
}
