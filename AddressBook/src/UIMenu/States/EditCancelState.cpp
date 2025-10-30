#include "EditCancelState.hpp"
#include <optional>
#include "../EditMenu.hpp"
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
	frame = uiMsgH.cancel(context.err, CancelType::Edit);
	frame(errorMsgH);
}

EditPhase EditCancelState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	bool yesNo = inputH.askYesNo();
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return EditPhase::EditCancel;
	}

	context.err = nullopt;
	if (yesNo) 
	{
		return EditPhase::ExitCancel;
	}
	else 
	{
		return EditPhase::EditStart;
	}
}
