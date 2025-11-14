#include "EditStartState.hpp"
#include <optional>
#include "EditMenu.hpp"
using namespace std;


void EditStartState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	if (owner_.getMode() == InputMode::AddEdit) 
	{
		frame = uiMsgH.addEditTitle();
	}
	else 
	{
		frame = uiMsgH.editTitle();
	}
	frame(errorMsgH);
	
	frame = uiMsgH.personalEdit(context.p);
	frame(errorMsgH);
	frame = uiMsgH.editConfirm();
	frame(errorMsgH);
	frame = uiMsgH.editInput(context.err);
	frame(errorMsgH);
}

EditPhase EditStartState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();
	context.menu = -1;

	ResultVariant result = inputH.getInt(IntRule::ZeroOrPositive, context.menu);
	if (!isVariantEqualTo<InputResult>(result, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(result);
		return EditPhase::EditStart;
	}

	context.err = nullopt;
	switch (context.menu) {
	case 0: return EditPhase::ExitCancel;
	case 9: return EditPhase::ExitSuccess;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		return EditPhase::EditItem;
	default: 
	{
		result = MenuSelectResult::WRONG_INDEX;
		context.err = wrapVariant<ResultVariant>(result);
		return EditPhase::EditStart;
	}
	}
}

