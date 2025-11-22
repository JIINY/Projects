#include "ViewActionMenuState.hpp"
#include <variant>
#include <optional>
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"
#include "ViewMenu.hpp"
using namespace std;


void ViewActionMenuState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.actionSubMenu(context.err);
	frame(errorMsgH);
	frame = uiMsgH.menuSelect(context.err);
	frame(errorMsgH);
}

ViewPhase ViewActionMenuState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	int input = -1;
	CommandPhase result = inputH.getViewPagingInput(input);

	switch (result) {
	case CommandPhase::Edit: 
	{
		context.err = nullopt;
		return ViewPhase::Edit;
	}
	case CommandPhase::Delete:
	{
		context.err = nullopt;
		return ViewPhase::DeleteConfirm;
	}
	case CommandPhase::Cancel:
	case CommandPhase::Enter:
	{
		context.err = nullopt;
		return ViewPhase::List;
	}
	default:
	{
		context.err = wrapVariant<ResultVariant>(MenuSelectResult::WRONG_COMMAND);
		return ViewPhase::Action;
	}
	}
}
