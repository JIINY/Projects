#include "AskAddCancelState.hpp"
#include <optional>
#include "../../Common/VariantUtils.hpp"
#include "../../UI/UICommonData.hpp"
#include "../../UI/UICommonHeader.hpp"

#include "../AddMenu.hpp"
using namespace std;


void AskAddCancelState::draw() 
{
	auto& context = owner_.getContext();
	auto& frame = owner_.getUIFrame();
	auto& uiMsgH = owner_.getUIMsgH();
	auto& errorMsgH = owner_.getErrorMsgH();

	frame = uiMsgH.addMenuLine(context.p);
	frame(errorMsgH);
	frame = uiMsgH.cancel(context.err, CancelType::Input);
	frame(errorMsgH);
}

AddPhase AskAddCancelState::update() 
{
	auto& context = owner_.getContext();
	auto& inputH = owner_.getInputH();

	bool yesNo = inputH.askYesNo();
	ResultVariant error = inputH.getLastError();
	if (!isVariantEqualTo<InputResult>(error, InputResult::SUCCESS)) 
	{
		context.err = wrapVariant<ResultVariant>(error);
		return AddPhase::AskAddCancel;
	}

	context.err = nullopt;
	if (yesNo)
	{
		return AddPhase::Exit;
	}
	else 
	{
		return AddPhase::AddReview;
	}
}
