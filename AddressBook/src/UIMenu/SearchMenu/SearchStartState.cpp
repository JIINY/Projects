#include "SearchStartState.hpp"
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "SearchMenu.hpp"
using namespace std;

void SearchStartState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.searchMenu();
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

SearchPhase SearchStartState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	ResultVariant result = inputH.getInt(IntRule::ZeroOrPositive, context.menu);
	if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(result);
		return SearchPhase::SearchStart;
	}

	context.err = nullopt;
	if (context.menu == 0) 
	{
		return SearchPhase::Exit;
	}
	return SearchPhase::SearchInputData;
}
