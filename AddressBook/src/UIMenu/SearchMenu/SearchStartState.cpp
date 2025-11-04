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

	context.menu = inputH.getInt(IntRule::ZeroOrPositive);
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return SearchPhase::SearchStart;
	}

	context.err = nullopt;
	if (context.menu == 0) 
	{
		return SearchPhase::Exit;
	}
	return SearchPhase::SearchInputData;
}
