#include "EditCancelState.hpp"
#include <optional>
#include "EditMenu.hpp"
#include "../../Common/VariantUtils.hpp"
using namespace std;


void EditCancelState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.editTitle();
	frame(errorMsgH);
	frame = uiMsgH.personalEdit(context.p);
	frame(errorMsgH);
	frame = uiMsgH.editConfirm();
	frame(errorMsgH);
	frame = uiMsgH.cancel(context.err, ActionType::Edit);
	frame(errorMsgH);
}

EditPhase EditCancelState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	ResultVariant result = inputH.askYesNo();
	context.err = nullopt;
	if (isVariantEqualTo <InputResult>(result, InputResult::YES))
	{
		return EditPhase::ExitCancel;
	}
	else if (isVariantEqualTo <InputResult>(result, InputResult::NO))
	{
		return EditPhase::EditStart;
	}

	context.err = wrapVariant<ResultVariant>(result);
	return EditPhase::EditCancel;
}

